/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * Stolen from linux (lib/crc7.c)
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef LIBS_CRC7_H
#define LIBS_CRC7_H

#include <stddef.h>
#include <stdint.h>

uint8_t crc7_be(uint8_t crc, const uint8_t *buffer, size_t len);

#endif

