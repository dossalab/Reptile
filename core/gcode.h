/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Stream GCode parser
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_GCODE_H
#define CORE_GCODE_H

#include <stddef.h>

struct gcode {

};

void gcode_parse(const void *block, size_t len);

#endif

