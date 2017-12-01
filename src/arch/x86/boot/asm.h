/*-- QiOS ---------------------------------------------------------------------*
 *                                                                             *
 *	Copyright (C) 2017, 2018 Liew Tze Wei                                      *
 *                                                                             *
 * 	This file is part of the QiOS kernel, and is made available under the      *
 *  terms of The Unlicense (That means just do whatever you want with the code *
 *  base).                                                                     *
 * 																			   *
 * ****************************************************************************/
#ifndef __ASM_H_
#define __ASM_H_

#include <stdint.h>

#define asm(x...) __asm__ __volatile__(x)

static inline __attribute__((section(".boot"))) uint32_t get_cr0(void) {
	uint32_t ret;
	asm("mov %0, cr0"
	    : "=r"(ret));

	return ret;
}

static inline void __attribute__((section(".boot"))) set_cr0(uint32_t val) {
	asm("mov cr0, %0" ::"r"(val));
}

static inline uint32_t __attribute__((section(".boot"))) get_cr3(void) {
	uint32_t ret;
	asm("mov %0, cr3"
	    : "=r"(ret));

	return ret;
}

static inline void __attribute__((section(".boot"))) set_cr3(uint32_t val) {
	asm("mov cr3, %0" ::"r"(val));
}

static inline uint32_t __attribute__((section(".boot"))) get_cr4(void) {
	uint32_t ret;
	asm("mov %0, cr4"
	    : "=r"(ret));

	return ret;
}

static inline void __attribute__((section(".boot"))) set_cr4(uint32_t val) {
	asm("mov cr4, %0" ::"r"(val));
}

#endif  // __ASM_H_