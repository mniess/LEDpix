#ifndef _PIXELS_H_
#define _PIXELS_H_

#include <avr/io.h>
#include "conf.h"

void init_pixels(void);

void render(uint8_t *rgb_arr);

#endif
