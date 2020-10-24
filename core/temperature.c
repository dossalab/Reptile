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

static struct task temperature_task;

static void temperature_task_handler(void)
{
	log_i("polling temperature...");
}

void temperature_system_init(void)
{
	task_init(&temperature_task, temperature_task_handler, \
				TEMPERATURE_POLL_INTERVAL);
}

