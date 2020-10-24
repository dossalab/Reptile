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
#include <core/print.h>
#include <misc/log.h>
#include <libs/fatfs/pff.h>

#define PRINT_FILENAME	"PRINTME.GCO"

static int file_reader(uint8_t *chunk, size_t size)
{
	size_t read;

	if (pf_read(chunk, size, &read) != FR_OK) {
		return -1;
	}

	return size;
}

static void on_drive_mounted(void *user)
{
	log_i("drive mounted, opening file...");

	if (pf_open(PRINT_FILENAME) != FR_OK) {
		log_e("unable to open file!");
		return;
	}

	log_i("print file ready");
	print_start(file_reader);
}

static void on_printing_started(void *user)
{
	log_i("printing started");
}

static void on_printing_done(void *user)
{
	log_i("printing done!");
}

void main(void)
{
	board_init();
	log_i("booting reptile...");

	task_system_init();
	drive_management_init();
	temperature_system_init();
	print_system_init();

	bus_subscribe(DRIVE_MOUNTED_MSG, on_drive_mounted);
	bus_subscribe(PRINTING_STARTED_MSG, on_printing_started);
	bus_subscribe(PRINTING_DONE_MSG, on_printing_done);

	irq_enable();
	log_i("ready");

	while (1) {
		tasks_update();
	}
}

