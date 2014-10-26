#include <avr/io.h>
#include <util/delay.h>
#include "pixels.h"

uint8_t rgb_arr[NUM_BYTES] = {0};

int main(void) {

    init_pixels();

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
