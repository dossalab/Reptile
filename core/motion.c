/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Motion algorithm
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <core/motion.h>
#include <mcu/common.h>
#include <stdlib.h> /* abs */

#define AXIS_COUNT	4

struct axis {
	int16_t start, end, delta;
	int16_t value, error, sign;
	struct gpio *port;
	int pin;
};

struct motion {
	struct axis *driving_axis;
	struct axis axes[AXIS_COUNT];
};

static void motion_update(struct motion *m)
{
	struct axis *a;

	for (int i = 0; i < AXIS_COUNT; i++) {
		a = &(m->axes[i]);

		// servo_set(&a->servo, a->value);

		if (a->value != a->end) {
			a->error += a->delta;
			if (2 * a->error >= m->driving_axis->delta) {
				a->value += a->sign;
				a->error -= m->driving_axis->delta;
			}
		}
	}
}

static void motion_execute(struct motion *m)
{
	struct axis *a;
	int max_index;
	int16_t max_delta = -1;

	for (int i = 0; i < AXIS_COUNT; i++) {
		a = &(m->axes[i]);

		a->delta = abs(a->end - a->start);
		a->value = a->start;
		a->error = 0;
		a->sign = (a->end > a->start)? 1 : -1;

		if (a->delta > max_delta) {
			max_delta = a->delta;
			max_index = i;
		}
	}

	m->driving_axis = &(m->axes[max_index]);
}

void motion_park(void)
{

}

void motion_move_to(int32_t x, int32_t y, int32_t z, int32_t a, bool absolute)
{

}

void motion_system_init(void)
{

}

