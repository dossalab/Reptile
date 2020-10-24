/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef MISC_LOG_H
#define MISC_LOG_H

#include <mcu/common.h>

#define log_e(format, ...) \
	uart_printf("[err]\t" format "\n\r", ##__VA_ARGS__)

#define log_i(format, ...) \
	uart_printf("[info]\t" format "\n\r", ##__VA_ARGS__)

#endif

