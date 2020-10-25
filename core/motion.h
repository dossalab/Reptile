/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Motion algorithm
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_MOTION_H
#define CORE_MOTION_H

#include <stdint.h>
#include <stdbool.h>

void motion_park(void);
void motion_move_to(int32_t x, int32_t y, int32_t z, int32_t a, bool absolute);
void motion_system_init(void);

#endif

