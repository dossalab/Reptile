/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * ARM Cortex-M architecture support. Tested on Cortex-m3/m4
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef ARCH_ARM_ARCH_H
#define ARCH_ARM_ARCH_H

#include <stdint.h>

static inline void irq_enable(void)
{
	asm volatile ("cpsie i" ::: "memory", "cc");
}

static inline bool irq_disable(void)
{
	uint32_t saved_primask;

	asm volatile(
		"mrs %0, primask\n"
		"cpsid i"
		: "=r" (saved_primask) :: "memory", "cc");

	return !saved_primask;
}

#endif

