/*-- QiOS ---------------------------------------------------------------------*
 *                                                                             *
 *	Copyright (C) 2017, 2018 Liew Tze Wei                                      *
 *                                                                             *
 * 	This file is part of the QiOS kernel, and is made available under the      *
 *  terms of The Unlicense (That means just do whatever you want with the code *
 *  base).                                                                     *
 * 																			   *
 *----------------------------------------------------------------------------*/
/*******************************************************************************
 *                                                                             *
 * C library function - memchr()                                               *
 * --------------------------------------------------------------------------- *
 * Description                                                                 *
 * ===========                                                                 *
 * The C library function void *memchr(const void *str, int c, size_t n)       *
 * searches for the first occurrence of the character c (an unsigned char) in  *
 * the first n bytes of the string pointed to, by the argument str.            *
 *                                                                             *
 * Declaration                                                                 *
 * ===========                                                                 *
 * void *memchr(const void *str, int c, size_t n)                              *
 *                                                                             *
 * Parameters                                                                  *
 * ==========                                                                  *
 * > str − This is the pointer to the block of memory where the search is      *
 *         performed.                                                          *
 * > c − This is the value to be passed as an int, but the function performs a *
 *       byte per byte search using the unsigned char conversion of *this      *
 *       value.                                                                *
 * > n − This is the number of bytes to be analyzed.                           *
 *                                                                             *
 * Return Value                                                                *
 * ============                                                                *
 * This function returns a pointer to the matching byte or NULL if the         *
 * character does not occur in the given memory area.                          *
 *                                                                             *
 ******************************************************************************/
#include <string.h>

void *memchr(const void *str, int c_in, size_t n) {
	if (!str) {
		return NULL;
	}

	const unsigned char *char_ptr;
	unsigned char c = (unsigned char)c_in;

#ifndef __TESTING
	size_t i = 0;
	for (char_ptr = (const char *)str;
	     char_ptr && i < n;
	     ++char_ptr, ++i) {
		if (*char_ptr == c) {
			return (void *)char_ptr;
		}
	}

	return NULL;
#else   // __TESTING
	const unsigned long int *longword_ptr;
	unsigned long int longword, magic_bits, charmask;

	// Handle the first few characters by reading one character at a time.
	// Do this until char_ptr is aligned on a longword boundary.  */
	for (char_ptr = (const char *)str;
	     ((unsigned long int)char_ptr & (sizeof(longword) - 1)) != 0 && n > 0;
	     ++char_ptr, n -= 4) {
		if (*char_ptr == c)
			return (void *)char_ptr;
		else if (*char_ptr == '\0')
			return NULL;

		/* All these elucidatory comments refer to 4-byte longwords,
    	 but the theory applies equally well to 8-byte longwords.  */

		longword_ptr = (unsigned long int *)char_ptr;
		/* Bits 31, 24, 16, and 8 of this number are zero.  Call these bits
		the "holes."  Note that there is a hole just to the left of
		each byte, with an extra at the end:

		bits:  01111110 11111110 11111110 11111111
		bytes: AAAAAAAA BBBBBBBB CCCCCCCC DDDDDDDD

		The 1-bits make sure that carries propagate to the next 0-bit.
		The 0-bits provide holes for carries to fall into.  */
		magic_bits = -1;
		magic_bits = magic_bits / 0xff * 0xfe << 1 >> 1 | 1;

		/* Set up a longword, each of whose bytes is C.  */
		charmask = c | (c << 8);
		charmask |= charmask << 16;
		if (sizeof(longword) > 4) {
			/* Do the shift in two steps to avoid a warning if long has 32 bits.  */
			charmask |= (charmask << 16) << 16;
		}

		if (sizeof(longword) > 8) {
			return NULL;
		}

		/* Instead of the traditional loop which tests each character,
		we will test a longword at a time.  The tricky part is testing
		if *any of the four* bytes in the longword in question are zero.
		*/
		for (;;) {
			/* We tentatively exit the loop if adding MAGIC_BITS to
			LONGWORD fails to change any of the hole bits of LONGWORD.

			1) Is this safe?  Will it catch all the zero bytes?
			Suppose there is a byte with all zeros.  Any carry bits
			propagating from its left will fall into the hole at its
			least significant bit and stop.  Since there will be no
			carry from its most significant bit, the LSB of the
			byte to the left will be unchanged, and the zero will be
			detected.

			2) Is this worthwhile?  Will it ignore everything except
			zero bytes?  Suppose every byte of LONGWORD has a bit set
			somewhere.  There will be a carry into bit 8.  If bit 8
			is set, this will carry into bit 16.  If bit 8 is clear,
			one of bits 9-15 must be set, so there will be a carry
			into bit 16.  Similarly, there will be a carry into bit
			24.  If one of bits 24-30 is set, there will be a carry
			into bit 31, so all of the hole bits will be changed.

			The one misfire occurs when bits 24-30 are clear and bit
			31 is set; in this case, the hole at bit 31 is not
			changed.  If we had access to the processor carry flag,
			we could close this loophole by putting the fourth hole
			at bit 32!

			So it ignores everything except 128's, when they're aligned
			properly.

			3) But wait!  Aren't we looking for C as well as zero?
			Good point.  So what we do is XOR LONGWORD with a longword,
			each of whose bytes is C.  This turns each byte that is C
			into a zero.  */

			longword = *longword_ptr++;
			n -= 4;

			/* Add MAGIC_BITS to LONGWORD.  */
			if ((((longword + magic_bits)

			      /* Set those bits that were unchanged by the addition.  */
			      ^ ~longword)

			     /* Look at only the hole bits.  If any of the hole bits
				 are unchanged, most likely one of the bytes was a zero.  */
			     & ~magic_bits) != 0 ||

			    /* That caught zeroes.  Now test for C.  */
			    ((((longword ^ charmask) + magic_bits) ^ ~(longword ^ charmask)) & ~magic_bits) != 0) {
				/* Which of the bytes was C or zero?
				If none of them were, it was a misfire; continue the search.  */

				char *cp = (char *)(longword_ptr - 1);

				if (*cp == c)
					return cp;
				else if (*cp == '\0')
					return NULL;
				if (*++cp == c)
					return cp;
				else if (*cp == '\0')
					return NULL;
				if (*++cp == c)
					return cp;
				else if (*cp == '\0')
					return NULL;
				if (*++cp == c)
					return cp;
				else if (*cp == '\0')
					return NULL;

				if (sizeof(longword) > 4) {
					if (*++cp == c)
						return cp;
					else if (*cp == '\0')
						return NULL;
					if (*++cp == c)
						return cp;
					else if (*cp == '\0')
						return NULL;
					if (*++cp == c)
						return cp;
					else if (*cp == '\0')
						return NULL;
					if (*++cp == c)
						return cp;
					else if (*cp == '\0')
						return NULL;
				}
			}
		}
	}

	return NULL;
#endif  //	__TESTING
}