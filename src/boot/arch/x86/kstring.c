#include "boot.h"

uint32_t strlen(const char* str) {
	uint32_t i = 0;
	while (str[i++] != '\0') {
	}

	return i - 1;
}

char *strcat(char *dest, const char *src) {
	for (; *dest != '\0'; dest++) {
	}

	while (*src != '\0') {
		*(dest++) = *(src++);
		*dest = '\0';
	}

	return dest;
}