/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Drive management module
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/drive.h>
#include <core/tasks.h>
#include <libs/fatfs/pff.h>
#include <misc/log.h>

static FATFS fatfs;
static struct task drive_management_task;
static bool drive_mounted = false;

static void drive_management_task_handler(void)
{
	if (drive_mounted) {
		return;
	}

	if (pf_mount(&fatfs) == FR_OK) {
		drive_mounted = true;
		bus_send(DRIVE_MOUNTED_MSG, NULL);
	}
}

bool drive_is_mounted(void)
{
	return drive_mounted;
}

void drive_management_init(void)
{
	task_init(&drive_management_task, drive_management_task_handler, \
				DRIVE_POLL_INTERVAL);
}

