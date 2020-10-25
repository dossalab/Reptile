/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * SD card support. Based on ChaN's avr_mmcp.c
 *
 * TODO:
 * - Check CCS bit in OCR register (CMD58)
 * - Ensure block sizes for different cards
 * - Test on older cards (SD1/MMC)
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <errno.h>
#include <stdint.h>
#include <stddef.h> /* size_t */
#include <drivers/sdcard.h>
#include <misc/endian.h>
#include <misc/delay.h>
#include <libs/crc7.h>

/* MMC/SDC commands */
#define CMD0	(0x40 + 0)	/* GO_IDLE_STATE */
#define CMD1	(0x40 + 1)	/* SEND_OP_COND (MMC) */
#define	ACMD41	(0xC0 + 41)	/* SEND_OP_COND (SDC) */
#define CMD8	(0x40 + 8)	/* SEND_IF_COND */
#define CMD16	(0x40 + 16)	/* SET_BLOCKLEN */
#define CMD17	(0x40 + 17)	/* READ_SINGLE_BLOCK */
#define CMD24	(0x40 + 24)	/* WRITE_BLOCK */
#define CMD55	(0x40 + 55)	/* APP_CMD */
#define CMD58	(0x40 + 58)	/* READ_OCR */

static inline uint8_t spi_read_one_byte(void)
{
	uint8_t byte;

	spi_recv(&byte, 1);
	return byte;
}

static inline void sdcard_select(struct sdcard *handle)
{
	spi_read_one_byte();
	gpio_clr(handle->cs_port, handle->cs_pin);
	spi_read_one_byte();
}

static inline void sdcard_unselect(struct sdcard *handle)
{
	gpio_set(handle->cs_port, handle->cs_pin);
	spi_read_one_byte();
}

/*
 * Send at least 80 pulses with CS high to wake up the card
 */
static inline void sdcard_wakeup(struct sdcard *handle)
{
	uint8_t dummy[10];

	gpio_set(handle->cs_port, handle->cs_pin);
	spi_recv(dummy, sizeof(dummy));
}

static uint8_t sdcard_send_cmd(struct sdcard *handle, uint8_t cmd, uint32_t arg)
{
	uint8_t packet[6];
	uint8_t answer;
	union u32_bytes temp;

	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
	if (cmd & 0x80) {
		cmd &= 0x7F;
		answer = sdcard_send_cmd(handle, CMD55, 0);
		if (answer > 1) return answer;
	}

	sdcard_select(handle);

	temp.u32 = cpu_to_be32(arg);

	packet[0] = cmd;
	packet[1] = temp.bytes[0];
	packet[2] = temp.bytes[1];
	packet[3] = temp.bytes[2];
	packet[4] = temp.bytes[3];
	packet[5] = crc7_be(0, packet, 5) | 0x01;

	spi_send(packet, sizeof(packet));

	/* Receive a command response */
	for (int i = 0; i < SDCARD_RECEIVE_RETRIES; i++) {
		answer = spi_read_one_byte();
		if ((answer & 0x80) == 0) {
			break;
		}
	}

	return answer;
}

static uint32_t sdcard_get_extended_answer(struct sdcard *card)
{
	union u32_bytes answer;

	spi_recv(answer.bytes, sizeof(answer.bytes));
	return be32_to_cpu(answer.u32);
}

bool sdcard_read(struct sdcard *handle, uint8_t *buff, uint32_t sector, \
					uint32_t offset, size_t count)
{
	uint8_t answer;
	uint32_t trailing;

	/* TODO: Convert to byte address if needed */

	if (sdcard_send_cmd(handle, CMD17, sector) != 0) {
		sdcard_unselect(handle);
		return false;
	}

	for (int i = 0; i < SDCARD_READ_TIMEOUT; i++) {
		spi_recv(&answer, 1);
		if (answer != 0xFF) {
			break;
		}
	}

	if (answer != 0xFE) {
		sdcard_unselect(handle);
		return false;
	}

	/* Data block arrived */
	trailing = 512 - offset - count;

	/* Skip leading bytes in the sector */
	while (offset--) {
		spi_read_one_byte();
	}

	spi_recv(buff, count);

	/* Skip trailing bytes in the sector */
	while (trailing--) {
		spi_read_one_byte();
	}

	sdcard_unselect(handle);
	return true;
}

/* just checks the pattern 0xAA */
static bool check_voltage_range(uint32_t extended_answer)
{
	return (extended_answer & 0xFF) == 0xAA;
}

static bool sdcard_detect_type(struct sdcard *handle)
{
	uint32_t extended_answer;

	handle->type = SDCARD_TYPE_UNKNOWN;

	if (sdcard_send_cmd(handle, CMD8, 0x1AA) == 0x01) {
		/* SDv2 */
		extended_answer = sdcard_get_extended_answer(handle);
		if (!check_voltage_range(extended_answer)) {
			sdcard_unselect(handle);
			return false;
		}

		handle->type = SDCARD_TYPE_SD2;
	} else {
		/* SDv1 or MMCv3 */
		if (sdcard_send_cmd(handle, ACMD41, 0) <= 1) {
			handle->type = SDCARD_TYPE_SD1;
		} else {
			handle->type = SDCARD_TYPE_MMC;
		}
	}

	sdcard_unselect(handle);
	return true;
}

static bool sdcard_wait_idle(struct sdcard *handle)
{
	uint8_t cmd;
	uint32_t arg = 0;

	switch (handle->type) {
		case SDCARD_TYPE_SD1:
			cmd = ACMD41;
			break;
		case SDCARD_TYPE_SD2:
			cmd = ACMD41;
			arg = (1UL << 30); /* HCS bit */
			break;
		case SDCARD_TYPE_MMC:
			cmd = CMD1;
			break;
		default:
			/* paranoia check */
			return false;
	}

	for (int i = 0; i < SDCARD_IDLE_TIMEOUT; i++) {
		if (sdcard_send_cmd(handle, cmd, arg) == 0x00) {
			sdcard_unselect(handle);
			return true;
		}

		delay_ms(1);
	}

	return false;
}

/*
 * Set block size to 512 (only for older SD1/MMC cards)
 */
static bool sdcard_ensure_block_size(struct sdcard *handle)
{
	if (handle->type != SDCARD_TYPE_SD1) {
		return true;
	}

	if (sdcard_send_cmd(handle, CMD16, 512) == 0x00) {
		sdcard_unselect(handle);
		return true;
	}

	return false;
}

bool sdcard_probe(struct sdcard *handle)
{
	sdcard_wakeup(handle);

	if (sdcard_send_cmd(handle, CMD0, 0) != 0x01) {
		sdcard_unselect(handle);
		return false;
	}

	if (!sdcard_detect_type(handle)) {
		sdcard_unselect(handle);
		return false;
	}

	if (!sdcard_wait_idle(handle)) {
		handle->type = SDCARD_TYPE_UNKNOWN;
		sdcard_unselect(handle);
		return false;
	}

	if (!sdcard_ensure_block_size(handle)) {
		handle->type = SDCARD_TYPE_UNKNOWN;
		sdcard_unselect(handle);
		return false;
	}

	sdcard_unselect(handle);
	return true;
}

void sdcard_init(struct sdcard *handle, struct gpio *cs_port, int cs_pin)
{
	handle->cs_port = cs_port;
	handle->cs_pin = cs_pin;
	handle->type = SDCARD_TYPE_UNKNOWN;

	gpio_out(handle->cs_port, handle->cs_pin);
}

