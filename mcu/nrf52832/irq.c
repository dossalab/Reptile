/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * NRF52832 interrupts support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>

#define DECLARE_IRQ_VECTORS
#include <arch/arm/declare-irq.h>

