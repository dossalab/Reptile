/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * arduino sample board support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <board/common.h>
#include <mcu/common.h>

void board_led_on(void)
{
	/* Not implemented */
}

void board_led_off(void)
{
	/* Not implemented */
}

void board_init(void)
{
	uart_init(UART_BAUD_9600);
}

