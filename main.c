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

#define HELLO_WORLD "Hello World by 173210"


void print(const char *s, int x, int y, char r, char g, char b, void *fbuf)
{
	int cur_x = x;
	int cur_y = y;
	int fnt_x, fnt_y;
	const char *cur;
	char *cur_fbuf;

	for (cur = s; *cur; cur++) {
		for (fnt_y = 0; fnt_y < FNT_HEIGHT; fnt_y++)
			for (fnt_x = 0; fnt_x < FNT_WIDTH; fnt_x++)
				if ((0x80 >> fnt_x) & fnt[*cur][fnt_y]) {
					cur_fbuf = (char *)(fbuf + ((cur_x + fnt_x) * 240 + (cur_y - fnt_y)) * 3);
					*cur_fbuf = b;
					*(cur_fbuf + 1) = g;
					*(cur_fbuf + 2) = r;
				}
		cur_x += FNT_WIDTH;
	}

}

void _start() __attribute__ ((section (".text.start")));
void _start()
{
	print(HELLO_WORLD, 0, TOP_HEIGHT, 255, 255, 255, (void *)TOP_LEFT_FRAME1);
	print(HELLO_WORLD, 0, TOP_HEIGHT, 255, 255, 255, (void *)TOP_LEFT_FRAME2);
}

