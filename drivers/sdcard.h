/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * SD card support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef DRIVERS_SDCARD_H
#define DRIVERS_SDCARD_H

#include <stdint.h>
#include <stdbool.h>
#include <mcu/common.h>

enum sdcard_type {
	SDCARD_TYPE_UNKNOWN,
	SDCARD_TYPE_SD1,
	SDCARD_TYPE_SD2,
	SDCARD_TYPE_MMC
};

struct sdcard {
	enum sdcard_type type;
	struct gpio *cs_port;
	int cs_pin;
};

#define SDCARD_IDLE_TIMEOUT	1000
#define SDCARD_RECEIVE_RETRIES	10
#define SDCARD_READ_TIMEOUT	4000

int sdcard_read(struct sdcard *handle, uint8_t *buff, uint32_t sector, \
					uint32_t offset, size_t count);

bool sdcard_probe(struct sdcard *handle);
void sdcard_init(struct sdcard *handle, struct gpio *cs_port, int cs_pin);

#endif

