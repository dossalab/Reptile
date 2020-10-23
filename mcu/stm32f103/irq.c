/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * STM32F103 (non-connectivity, non-xl-density) interrupts support
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#include <mcu/common.h>

#define DECLARE_IRQ_VECTORS
#include <arch/arm/declare-irq.h>

