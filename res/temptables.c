/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * NTC thermistor tables
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <res/temptables.h>
#include <misc/stuff.h>

static struct ntc_table_entry epson_100k_conversion[] = {
	{ .adc = 1,    .temp = 350 },
	{ .adc = 28,   .temp = 250 },
	{ .adc = 31,   .temp = 245 },
	{ .adc = 35,   .temp = 240 },
	{ .adc = 39,   .temp = 235 },
	{ .adc = 42,   .temp = 230 },
	{ .adc = 44,   .temp = 225 },
	{ .adc = 49,   .temp = 220 },
	{ .adc = 53,   .temp = 215 },
	{ .adc = 62,   .temp = 210 },
	{ .adc = 71,   .temp = 205 },
	{ .adc = 78,   .temp = 200 },
	{ .adc = 94,   .temp = 190 },
	{ .adc = 102,  .temp = 185 },
	{ .adc = 116,  .temp = 170 },
	{ .adc = 143,  .temp = 160 },
	{ .adc = 183,  .temp = 150 },
	{ .adc = 223,  .temp = 140 },
	{ .adc = 270,  .temp = 130 },
	{ .adc = 318,  .temp = 120 },
	{ .adc = 383,  .temp = 110 },
	{ .adc = 413,  .temp = 105 },
	{ .adc = 439,  .temp = 100 },
	{ .adc = 484,  .temp = 95  },
	{ .adc = 513,  .temp = 90  },
	{ .adc = 607,  .temp = 80  },
	{ .adc = 664,  .temp = 70  },
	{ .adc = 781,  .temp = 60  },
	{ .adc = 810,  .temp = 55  },
	{ .adc = 849,  .temp = 50  },
	{ .adc = 914,  .temp = 45  },
	{ .adc = 914,  .temp = 40  },
	{ .adc = 935,  .temp = 35  },
	{ .adc = 954,  .temp = 30  },
	{ .adc = 970,  .temp = 25  },
	{ .adc = 978,  .temp = 22  },
	{ .adc = 1008, .temp = 3   },
	{ .adc = 1023, .temp = 0   },
};

struct ntc_table epson_100k = {
	.size = ARRAY_LEN(epson_100k_conversion),
	.entries = epson_100k_conversion
};

