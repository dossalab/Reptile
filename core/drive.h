/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Drive management module
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef CORE_DRIVE_H
#define CORE_DRIVE_H

#include <core/bus.h>

#define DRIVE_MOUNTED_MSG	0xDD
#define DRIVE_POLL_INTERVAL	500

void drive_management_init(void);

#endif

