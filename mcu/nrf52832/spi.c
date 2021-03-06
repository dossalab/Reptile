/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * NRF52832 legacy mode SPI (without EasyDMA)
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>
#include <misc/stuff.h>

/*
 * Config register values
 */

/* Bit order (0: msb first, 1: lsb first) */
#define CONFIG_ORDER_BIT	BIT(0)

/* Clock phase (0: sample on leading, 1: sample on trailing) */
#define CONFIG_CPHA_BIT		BIT(1)

/* Clock polarity (0: active high, 1: active low) */
#define CONFIG_CPOL_BIT		BIT(2)

/*
 * Enable register values
 */

#define NRF_SPI_ENABLE	1

void spi_send(void *data, size_t len)
{
	uint8_t *ptr = data;

	while (len--) {
		NRF_SPI0->TXD = *(ptr++);

		while (!NRF_SPI0->EVENTS_READY) {
			;;
		}

		/* ignore read */
		(void)NRF_SPI0->RXD;
		NRF_SPI0->EVENTS_READY = 0;
	}
}

void spi_recv(void *data, size_t len)
{
	uint8_t *ptr = data;

	while (len--) {
		/* Send dummy 0xFF to get data from the device */
		NRF_SPI0->TXD = 0xFF;

		while (!NRF_SPI0->EVENTS_READY) {
			;;
		}

		*(ptr++) = NRF_SPI0->RXD;
		NRF_SPI0->EVENTS_READY = 0;
	}
}

void spi_init(int mosi, int miso, int sck)
{
	NRF_SPI0->MOSI = mosi;
	NRF_SPI0->MISO = miso;
	NRF_SPI0->SCK = sck;

	/* Msb first, sample on leading edge, polarity - active high */
	NRF_SPI0->CONFIG &= \
		~(CONFIG_ORDER_BIT | CONFIG_CPHA_BIT | CONFIG_CPOL_BIT);

	NRF_SPI0->FREQUENCY = SPI_FREQUENCY_M8;
	NRF_SPI0->ENABLE = NRF_SPI_ENABLE;
}

