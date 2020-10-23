/*
 * Part of the Reptile - simple 3d printer firmware
 *
 * AVR support.
 *
 * See LICENSE.md for licensing information
 * Roman Luitko, 2020
 */

#ifndef ARCH_AVR_ARCH_H
#define ARCH_AVR_ARCH_H

#include <stdint.h>
#include <avr/interrupt.h>

static inline void irq_enable(void)
{
	asm volatile ("sei" ::: "memory", "cc");
}

static inline bool irq_disable(void)
{
	uint8_t saved_sreg;

	saved_sreg = SREG;
	asm volatile ("cli" ::: "memory", "cc");

	return !!(saved_sreg & SREG_I);
}
#endif

