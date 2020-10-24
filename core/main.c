/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <arch/common.h>
#include <board/common.h>
#include <core/tasks.h>
#include <core/temperature.h>
#include <misc/log.h>

void main(void)
{
	board_init();
	log_i("booting reptile...");

	task_system_init();
	temperature_system_init();
	irq_enable();

	log_i("ready");

	while (1) {
		tasks_update();
	}
}

