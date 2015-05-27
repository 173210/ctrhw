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

int cur_x = 0;
int cur_y = TOP_HEIGHT;

void _puts(const char *s)
{
	struct px {
		char b;
		char g;
		char r;
	};

	struct px (* const top_frames[])[TOP_HEIGHT] = {(void *)0xF0184E60, (void *)0xF01CB370};
	static const struct px bg_px = {0, 0, 0};
	static const struct px fnt_px = {255, 255, 255};
	const struct px *cur_px;
	int i, x, y, fnt_x, fnt_y;

	while (1) {
		switch (*s) {
			case '\0':
				return;
			case '\b':
				cur_x -= FNT_WIDTH;
				break;
			case '\t':
				cur_x += FNT_WIDTH * 4;
				break;
			case '\n':
				cur_x = 0;
			case '\v':
				cur_y -= FNT_HEIGHT;
				if (cur_y < 0)
					cur_y = TOP_HEIGHT;
			case '\r':
				break;
			case '\x7F':
				s++;
				break;
			default:
				if (cur_x + FNT_WIDTH > TOP_WIDTH) {
					cur_x = 0;
					cur_y -= FNT_HEIGHT;
					if (cur_y < 0)
						cur_y = TOP_HEIGHT;
				}

				for (fnt_y = 0; fnt_y < FNT_HEIGHT; fnt_y++) {
					y = cur_y - fnt_y;
					for (fnt_x = 0; fnt_x < FNT_WIDTH; fnt_x++) {
						x = cur_x + fnt_x;
						cur_px = (0x80 >> fnt_x) & fnt[*s][fnt_y] ? &fnt_px : &bg_px;

						for (i = 0; i < sizeof(top_frames) / sizeof(void *); i++) {
							top_frames[i][x][y].r = cur_px->r;
							top_frames[i][x][y].g = cur_px->g;
							top_frames[i][x][y].b = cur_px->b;
						}
					}
				}

				cur_x += FNT_WIDTH;
		}

		s++;
	}

}

char *itoa(int val, char *buf, int base)
{
	static const char digits [] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *start = buf;
	char *tmp_buf = buf;
	char tmp;
	int sign = 0;
	int quot, rem;

	if (base >= 2 && base <= 36) {
		if (base == 10 && (sign = val) < 0)
			val = -val;

		do {
			quot = (unsigned)val / base;
			rem = (unsigned)val % base;
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
