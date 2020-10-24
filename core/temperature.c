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
#include <mcu/common.h>
#include <board/common.h>
#include <stdbool.h>

static struct task temperature_task;
static struct thermistor hotend_thermistor;
static struct thermistor heatbed_thermistor;
static bool is_heating = false;
static int hotend_temp_setting, heatbed_temp_setting;

#define hotend_heater_on() \
	gpio_set(BOARD_HOTEND_HEATER_PORT, BOARD_HOTEND_HEATER_PIN)
#define hotend_heater_off() \
	gpio_clr(BOARD_HOTEND_HEATER_PORT, BOARD_HOTEND_HEATER_PIN)

#define heatbed_heater_on() \
	gpio_set(BOARD_HEATBED_HEATER_PORT, BOARD_HEATBED_HEATER_PIN)
#define heatbed_heater_off() \
	gpio_clr(BOARD_HEATBED_HEATER_PORT, BOARD_HEATBED_HEATER_PIN)

static void temperature_task_handler(void)
{
	int heatbed_temp, hotend_temp;

	if (is_heating) {
		hotend_temp = thermistor_read(&hotend_thermistor);
		heatbed_temp = thermistor_read(&heatbed_thermistor);

		log_i("temperature: %d°C hotend, %d°C heatbed", \
				hotend_temp, heatbed_temp);

		if (hotend_temp < hotend_temp_setting) {
			hotend_heater_on();
		} else {
			hotend_heater_off();
		}

		if (heatbed_temp < heatbed_temp_setting) {
			heatbed_heater_on();
		} else {
			heatbed_heater_off();
		}
	}
}

void temperature_start_heating(int hotend_temp, int heatbed_temp)
{
	is_heating = true;
	hotend_temp_setting = hotend_temp;
	heatbed_temp_setting = heatbed_temp;
}

void temperature_stop_heating(void)
{
	is_heating = false;
	hotend_temp_setting = -1;
	heatbed_temp_setting = -1;

	hotend_heater_off();
	heatbed_heater_off();
}

void temperature_system_init(void)
{
	thermistor_init(&hotend_thermistor, HOTEND_ADC_CHANNEL);
	thermistor_init(&heatbed_thermistor, HEATBED_ADC_CHANNEL);

	task_init(&temperature_task, temperature_task_handler, \
				TEMPERATURE_POLL_INTERVAL);
}

