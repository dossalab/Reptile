/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Global message bus
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <stdlib.h> /* calloc */
#include <core/bus.h>
#include <misc/stuff.h>

static volatile DECLARE_LIST(subscription_list);

#define node_to_sub(_node) \
	container_of(_node, struct subscription, node);

#define sub_to_node(subscription) \
	&(subscription)->node

void bus_send(int topic, void *content)
{
	struct list_node *ptr;
	struct subscription *s;

	list_forward(ptr, &subscription_list) {
		s = node_to_sub(ptr);
		if (s->topic == topic) {
			s->handler(content);
		}
	}
}

void bus_subscribe(int topic, void (*handler)(void *))
{
	struct subscription *sub;

	sub = calloc(1, sizeof(struct subscription));
	if (!sub) {
		return;
	}

	sub->topic = topic;
	sub->handler = handler;

	list_add_after(&subscription_list, sub_to_node(sub));
}

