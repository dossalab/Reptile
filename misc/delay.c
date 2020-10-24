/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Stupid delay, like really
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <misc/delay.h>

void delay_ms(uint32_t ms)
{
	volatile unsigned long n = ms * 1000;
	while (n--);
}

