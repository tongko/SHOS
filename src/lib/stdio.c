/*-- QiOS ---------------------------------------------------------------------*
 *                                                                             *
 *	Copyright (C) 2017, 2018 Liew Tze Wei                                      *
 *                                                                             *
 * 	This file is part of the QiOS kernel, and is made available under the      *
 *  terms of The Unlicense (That means just do whatever you want with the code *
 *  base).                                                                     *
 * ****************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/term.h>

int32_t sprintf(unsigned char *str, const char *format, ...) {
	va_list arg;
	va_start(arg, format);
	vsprintf(&str, format, arg);
	va_end(arg);
}

int32_t printf(const string_t *format, ...) {
	unsigned char buffer[1024] = {0};
	string_t str;
	makestr(&str, buffer);

	va_list arg;
	va_start(arg, format);
	vsprintf(&str, format, arg);
	va_end(arg);

	int32_t i = 0;
	while (buffer[i] != '\0') {
		term.putc(buffer[i++]);
	}
}