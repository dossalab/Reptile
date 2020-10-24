/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Temperature control
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/tasks.h>
#include <misc/log.h>
#include <core/temperature.h>
#include <drivers/thermistor.h>
#include <board/common.h>

static struct task temperature_task;
static struct thermistor hotend_thermistor;
static struct thermistor heatbed_thermistor;

static void temperature_task_handler(void)
{
	int heatbed_temp, hotend_temp;

	hotend_temp = thermistor_read(&hotend_thermistor);
	heatbed_temp = thermistor_read(&heatbed_thermistor);

	log_i("temperature: %d°C hotend, %d°C heatbed", \
			hotend_temp, heatbed_temp);
}

void temperature_system_init(void)
{
	thermistor_init(&hotend_thermistor, HOTEND_ADC_CHANNEL);
	thermistor_init(&heatbed_thermistor, HEATBED_ADC_CHANNEL);

	task_init(&temperature_task, temperature_task_handler, \
				TEMPERATURE_POLL_INTERVAL);
}

