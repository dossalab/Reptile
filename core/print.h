/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Print process control
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_PRINT_H
#define CORE_PRINT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define STREAM_POLL_INTERVAL	100

#define PRINTING_STARTED_MSG	0x75
#define PRINTING_DONE_MSG	0x7D

typedef int (*stream_read_t)(uint8_t *, size_t);

bool print_start(stream_read_t reader);
void print_stop(void);

void print_system_init(void);

#endif

