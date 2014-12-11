/*
 * main.c
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


#include <avr/io.h>
#include <util/delay.h>
#include "pixels.h"
#include "stdlib.h"

//uint8_t rgb_arr[NUM_BYTES] = {0};

int main(void) {

    init_pixels();
    
    uint8_t* rgb_arr = (uint8_t*)malloc(NUM_BYTES);

    uint8_t *p = &rgb_arr[NUM_BYTES-3];
    while (1) {
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        if (p >= &rgb_arr[NUM_BYTES]) p = rgb_arr;
        *(p) = 180;
        *(p+1) = 255;
        *(p+2) = 0;
        
        render(rgb_arr);
        _delay_ms(50);
    }
    
    return 0; 
}
