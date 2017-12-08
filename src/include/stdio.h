/*-- QiOS ---------------------------------------------------------------------*
 *                                                                             *
 *	Copyright (C) 2017, 2018 Liew Tze Wei *
 *                                                                             *
 * 	This file is part of the QiOS kernel, and is made available under the *
 *  terms of The Unlicense (That means just do whatever you want with the code *
 *  base).                                                                     *
 * ****************************************************************************/
#ifndef __STDIO_H_
#define __STDIO_H_

#include <stdint.h>

#include <stdarg.h>

#include <stddef.h>

uint32_t sprintf(char *str, const char *format, ...);
uint32_t vsprintf(char *str, const char *format, va_list arg);
uint32_t printf(const char *format, ...);

#endif  //	__STDIO_H_