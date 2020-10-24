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
#include <core/drive.h>
#include <core/bus.h>
#include <misc/log.h>
#include <libs/fatfs/pff.h>

#define PRINT_FILENAME	"PRINTME.GCO"

static void on_drive_mounted(void *user)
{
	log_i("drive mounted, opening file...");

	if (pf_open(PRINT_FILENAME) != FR_OK) {
		log_e("unable to open file!");
		return;
	}

	log_i("print file ready");
}

void main(void)
{
	board_init();
	log_i("booting reptile...");

	task_system_init();
	drive_management_init();
	temperature_system_init();

	bus_subscribe(DRIVE_MOUNTED_MSG, on_drive_mounted);
	irq_enable();
	log_i("ready");

	while (1) {
		tasks_update();
	}
}

