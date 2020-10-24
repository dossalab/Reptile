/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Global message bus
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_BUS_H
#define CORE_BUS_H

#include <misc/list.h>

struct subscription {
	struct list_node node;

	int topic;
	void (*handler)(void *);
};

void bus_send(int topic, void *content);
void bus_subscribe(int topic, void (*handler)(void *));

#endif

