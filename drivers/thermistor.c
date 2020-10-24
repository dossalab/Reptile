/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Thermistor 'support'
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>
#include <drivers/thermistor.h>

int thermistor_read(struct thermistor *handle)
{
	int adc_raw;

	adc_raw = adc_read(handle->adc_channel);
	return 0;
}

void thermistor_init(struct thermistor *handle, int adc_channel)
{
	handle->adc_channel = adc_channel;
	adc_init(handle->adc_channel);
}

