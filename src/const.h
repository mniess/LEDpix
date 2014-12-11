/*
 * conf.h
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


#ifndef _CONF_H_
#define _CONF_H_

#define NUM_RGB   (240)

#define OUT_PORT  (PORTB)
#define OUT_DR    (DDRB)
#define OUT_PIN_1 (PB0)
#define OUT_PIN_2 (PB1)
#define OUT_PIN_3 (PB2)

#define NUM_BYTES (NUM_RGB*3)

#endif
