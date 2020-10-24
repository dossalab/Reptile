/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_LOG_H
#define MISC_LOG_H

#include <mcu/common.h>

#define log_e(...) \
	uart_printf("[err]\t" __VA_ARGS__ "\n\r")

#define log_i(...) \
	uart_printf("[info]\t" __VA_ARGS__ "\n\r")

#endif

