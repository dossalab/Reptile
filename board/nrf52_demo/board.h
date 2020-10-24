/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * NRF52 demo board support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef BOARD_NRF52_DEMO_H
#define BOARD_NRF52_DEMO_H

#define BOARD_LED_PORT			NRF_P0
#define BOARD_LED_PIN			8

/* UART */
#define BOARD_UART_TX_PIN		20
#define BOARD_UART_RX_PIN		19

/* SPI */
#define BOARD_SPI_MOSI_PIN		25
#define BOARD_SPI_MISO_PIN		26
#define BOARD_SPI_SCK_PIN		27

/* SD card */
#define BOARD_SDCARD_CS_PORT		NRF_P0
#define BOARD_SDCARD_CS_PIN		28

/* ADC (thermistors) */
#define HOTEND_ADC_CHANNEL		0
#define HEATBED_ADC_CHANNEL		1

/* Heaters */
#define BOARD_HOTEND_HEATER_PORT	NRF_P0
#define BOARD_HOTEND_HEATER_PIN		1
#define BOARD_HEATBED_HEATER_PORT	NRF_P0
#define BOARD_HEATBED_HEATER_PIN	2

#endif

