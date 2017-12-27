/*-- QiOS ---------------------------------------------------------------------*
 *                                                                             *
 *	Copyright (C) 2017, 2018 Liew Tze Wei                                      *
 *                                                                             *
 * 	This file is part of the QiOS kernel, and is made available under the      *
 *  terms of The Unlicense (That means just do whatever you want with the code *
 *  base).                                                                     *
 * 																			   *
 * ****************************************************************************/
#ifndef __KSTR_H_
#define __KSTR_H_

#include <attribs.h>
#include <kdef.h>
#include <stdint.h>

#ifndef ISDIGIT
#define ISDIGIT(x) (x >= 0x30 && x <= 0x39)
#endif

__early size_t strlen(const char *str);
__early char *strcat(char *dest, const char *src);
__early int strcmp(const char *str1, const char *str2);
__early void *memcpy(void *dest, const void *src, size_t n);
__early void *memset(void *dest, char c, size_t count);
__early void reverse(char *str);
__early char *strchr(const char *s, int c_in);

#endif  //	__KSTR_H_