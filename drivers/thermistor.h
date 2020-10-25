/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Thermistor 'support'
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef DRIVERS_THERMISTOR_H
#define DRIVERS_THERMISTOR_H

#include <res/temptables.h>

struct thermistor {
	int adc_channel;
	struct ntc_table *table;
};

/* temperature in millidegree */
int thermistor_read(struct thermistor *handle);
void thermistor_init(struct thermistor *handle, struct ntc_table *table, \
				int adc_channel);

#endif

