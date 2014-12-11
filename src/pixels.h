/*
 * pixels.h
 * This file is part of LEDpix
 *
 * Copyright (C) 2014 - Florian Rommel
 *
 * LEDpix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * LEDpix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LEDpix. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _PIXELS_H_
#define _PIXELS_H_

#include <avr/io.h>
#include "const.h"

void init_pixels(void);

void render(uint8_t *rgb_arr);

#endif
