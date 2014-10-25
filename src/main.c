#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "pixels.h"

int main(void) {

    DDRB |= (1 << PB0);
    DDRB |= (1 << PB1);
    DDRB |= (1 << PB2);
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
    PORTB &= ~(1 << PB2);

    uint8_t rgb_arr[NUM_BYTES] = {0};

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
