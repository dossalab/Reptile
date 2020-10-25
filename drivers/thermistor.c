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
#include <misc/log.h>

static int16_t conversion_table_lookup(struct ntc_table *table, int16_t adc)
{
	return -1;
}

int thermistor_read(struct thermistor *handle)
{
	return conversion_table_lookup(
		handle->table,
		adc_read(handle->adc_channel)
	);
}

void thermistor_init(struct thermistor *handle, struct ntc_table *table, \
				int adc_channel)
{
	handle->adc_channel = adc_channel;
	handle->table = table;
	adc_init(handle->adc_channel);
}

