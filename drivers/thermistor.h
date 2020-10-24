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

struct thermistor {
	int adc_channel;
};

/* temperature in millidegree */
int thermistor_read(struct thermistor *handle);
void thermistor_init(struct thermistor *handle, int adc_channel);

#endif

