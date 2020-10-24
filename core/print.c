/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Print process control
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/print.h>
#include <core/tasks.h>
#include <misc/log.h>
#include <core/drive.h>
#include <core/bus.h>
#include <core/temperature.h>

static struct task stream_reader_task;
static stream_read_t stream_reader;
static bool is_printing = false;

bool print_start(stream_read_t reader)
{
	if (is_printing) {
		return false;
	}

	stream_reader = reader;
	is_printing = true;
	bus_send(PRINTING_STARTED_MSG, NULL);

	return true;
}

void print_stop(void)
{
	is_printing = false;
	bus_send(PRINTING_DONE_MSG, NULL);
}

static void stream_reader_handler(void)
{
	static uint8_t buffer[512];
	int read;

	if (!is_printing) {
		return;
	}

	read = stream_reader(buffer, sizeof(buffer));
	if (read <= 0) {
		bus_send(PRINTING_DONE_MSG, NULL);
		is_printing = false;
		return;
	}
}

void print_system_init(void)
{
	task_init(&stream_reader_task, stream_reader_handler, \
				STREAM_POLL_INTERVAL);
}

