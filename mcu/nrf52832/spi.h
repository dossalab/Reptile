/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * NRF52832 legacy mode SPI (without EasyDMA)
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MCU_NRF52832_SPI_H
#define MCU_NRF52832_SPI_H

#include <stdint.h>
#include <stddef.h>

/* This magic values were taken from NRF52832 datasheet */
#define SPI_FREQUENCY_K125	0x02000000UL
#define SPI_FREQUENCY_K250	0x04000000UL
#define SPI_FREQUENCY_K500	0x08000000UL
#define SPI_FREQUENCY_M1	0x10000000UL
#define SPI_FREQUENCY_M2	0x20000000UL
#define SPI_FREQUENCY_M4	0x40000000UL
#define SPI_FREQUENCY_M8	0x80000000UL

struct spi {
	volatile uint32_t __reserved_0[66];
	volatile uint32_t EVENTS_READY;
	volatile uint32_t __reserved_1[126];
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t __reserved_2[125];
	volatile uint32_t ENABLE;
	volatile uint32_t __reserved_3;

	struct {
		volatile uint32_t SCK;
		volatile uint32_t MOSI;
		volatile uint32_t MISO;
	};

	volatile uint32_t __reserved_4;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t __reserved_5;
	volatile uint32_t FREQUENCY;
	volatile uint32_t __reserved_6[11];
	volatile uint32_t CONFIG;
};

#define NRF_SPI0_BASE		0x40003000UL
#define NRF_SPI0		((struct spi *)NRF_SPI0_BASE)

void spi_init(int mosi, int miso, int sck);

#endif

