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

enum gcode_command {
	GCODE_UNKNOWN,
	GCODE_G1,	/* move (X, Y, Z, E - coordinates, F - feedrate) */
	GCODE_G28,	/* home all axes */
	GCODE_G20,	/* set units to inches */
	GCODE_G21,	/* set units to millimeters */
	GCODE_G90,	/* set absolute positioning */
	GCODE_G91,	/* set relative positioning */
	GCODE_G92,	/* set current position */
	GCODE_M82,	/* set extruder to absolute mode */
	GCODE_M84,	/* disarm motors */
	GCODE_M104,	/* set extruder temperature (arg: S - temp) */
	GCODE_M106,	/* fan on (S - PWM value (0...255)) */
	GCODE_M107,	/* fan off */
	GCODE_M109,	/* set extruder temperature and wait (arg: S - temp) */
};

struct gcode {

};

void gcode_parse(const void *block, size_t len);

#endif

