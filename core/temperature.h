/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Temperature control
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_TEMPERATURE_H
#define CORE_TEMPERATURE_H

#define TEMPERATURE_POLL_INTERVAL	1000

void temperature_start_heating(int hotend_temp, int heatbed_temp);
void temperature_stop_heating(void);

void temperature_system_init(void);

#endif

