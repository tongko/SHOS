/*-- QiOS ---------------------------------------------------------------------*
 *                                                                             *
 *	Copyright (C) 2017, 2018 Liew Tze Wei                                      *
 *                                                                             *
 * 	This file is part of the QiOS kernel, and is made available under the      *
 *  terms of The Unlicense (That means just do whatever you want with the code *
 *  base).                                                                     *
 * 																			   *
 * ****************************************************************************/
#ifndef __MEMORY_H_
#define __MEMORY_H_

#include <attribs.h>
#include <kernel/init.h>
#include <mem/paging.h>
#include <mem/pmm.h>

void mm_init(setup_info_t *setup_info);
uint32_t mm_total_physical(void);
uint32_t mm_used_physical(void);

#endif  //	__MEMORY_H_