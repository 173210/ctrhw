/*
 * Copyright (C) 2014 173210 <root.3.173210@live.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "fnt.h"


#define TOP_HEIGHT 240
#define TOP_WIDTH 400
#define TOP_LEFT_FRAME1 (void *)0xF0184E60
#define TOP_LEFT_FRAME2 (void *)0xF01CB370


int cur_x = 0;
int cur_y = TOP_HEIGHT;

void _puts(const char *s)
{
	int fnt_x, fnt_y;
	const char *cur;
	char *cur_fbuf1;
	char *cur_fbuf2;

	for (cur = s; *cur; cur++) {
		if (*cur == '\n') {
			cur_x = 0;
			cur_y -= FNT_HEIGHT;
			if (cur_y < 0)
				cur_y = TOP_HEIGHT;

			continue;
		}
		if (cur_x + FNT_WIDTH > TOP_WIDTH) {
			cur_x = 0;
			cur_y -= FNT_HEIGHT;
			if (cur_y < 0)
				cur_y = TOP_HEIGHT;
		}

		for (fnt_y = 0; fnt_y < FNT_HEIGHT; fnt_y++)
			for (fnt_x = 0; fnt_x < FNT_WIDTH; fnt_x++) {
				cur_fbuf1 = (char *)(TOP_LEFT_FRAME1 + ((cur_x + fnt_x) * TOP_HEIGHT + (cur_y - fnt_y)) * 3);
				cur_fbuf2 = (char *)(TOP_LEFT_FRAME2 + ((cur_x + fnt_x) * TOP_HEIGHT + (cur_y - fnt_y)) * 3);

				if ((0x80 >> fnt_x) & fnt[*cur][fnt_y]) {
					*cur_fbuf1 = *cur_fbuf2 = 255;			// blue
					*(cur_fbuf1 + 1) = *(cur_fbuf2 + 1) = 255;	// green
					*(cur_fbuf1 + 2) = *(cur_fbuf2 + 2) = 255;	// red
				} else {
					*cur_fbuf1 = *cur_fbuf2 = 0;			// blue
					*(cur_fbuf1 + 1) = *(cur_fbuf2 + 1) = 0;	// green
					*(cur_fbuf1 + 2) = *(cur_fbuf2 + 2) = 0;	// red
				}
			}

		cur_x += FNT_WIDTH;
	}

}

char *itoa(int val, char *buf, int base)
{
	static const char digits [] = "0123456789ABCDEF";
	char *start = buf;
	char *tmp_buf = buf;
	char tmp;
	int sign = 0;
	int quot, rem;

	if (base >= 2 && base <= 16) {
		if (base == 10 && (sign = val) <0)
			val = -val;

		do {
			quot = val / base;
			rem = val % base;
			*buf++ = digits[rem];
		} while ((val = quot));

		if (sign < 0)
			*buf++ = '-';

		*buf-- = '\0';
		while (buf > tmp_buf) {
			tmp = *buf;
			*buf-- = *tmp_buf;
			*tmp_buf++ = tmp;
		}
	} else *buf = '\0';

	return start;
}

void _start() __attribute__ ((section (".text.start")));
void _start()
{
	char buf[4];

	_puts("Hello World on 3DS by 173210\n\n"

		"Kernel Version: ");
	_puts(itoa(*(char *)0x1FF80003, buf, 10));
	_puts(".");
	_puts(itoa(*(char *)0x1FF80002, buf, 10));
	_puts("-");
	_puts(itoa(*(char *)0x1FF80001, buf, 10));

	_puts("\nKernel CTR-SDK Version: ");
	_puts(itoa(*(char *)0x1FF80018, buf, 10));

	_puts("\nFirmware Version: ");
	_puts(itoa(*(char *)0x1FF80063, buf, 10));
	_puts(".");
	_puts(itoa(*(char *)0x1FF80062, buf, 10));
	_puts("-");
	_puts(itoa(*(char *)0x1FF80061, buf, 10));

	_puts("\nFirmware CTR-SDK Version: ");
	_puts(itoa(*(char *)0x1FF80068, buf, 10));

	_puts("\nDebug Unit?: ");
	_puts(*(char *)0x1FF80015 ? "Yes\n" : "No\n");
}
