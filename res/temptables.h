/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * NTC thermistor tables
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef RES_TEMPTABLES_H
#define RES_TEMPTABLES_H

#include <stdint.h>
#include <stddef.h>

struct ntc_table_entry {
	uint16_t adc;
	uint16_t temp;
};

struct ntc_table {
	size_t size;
	struct ntc_table_entry *entries;
};

extern struct ntc_table epson_100k;

#endif

