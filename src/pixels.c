#include <avr/io.h>
#include <avr/interrupt.h>
#include "pixels.h"

void rearrange(uint8_t *rgb_arr) {
    uint8_t *ps = &rgb_arr[60];
    uint8_t *pe = &rgb_arr[120];
    
    asm (
        "        ldi r18, 10\n\t"
        "        ldi r19, 6\n\t"
        
        "rearr:  ld r20, %a[ps]\n\t"
        "        ldd r21, %a[ps]+1\n\t"
        "        ldd r22, %a[ps]+2\n\t"
        "        ld r25, -%a[pe]\n\t"
        "        ld r24, -%a[pe]\n\t"
        "        ld r23, -%a[pe]\n\t"
        "        st %a[pe], r20\n\t"
        "        std %a[pe]+1, r21\n\t"
        "        std %a[pe]+2, r22\n\t"
        "        st %a[ps]+, r23\n\t"
        "        st %a[ps]+, r24\n\t"
        "        st %a[ps]+, r25\n\t"
        "        dec r18\n\t"
        "        brne rearr\n\t"
        "        subi r28,-90\n\t"  //TODO
	    "        sbci r29,-1\n\t"
        "        subi r30,-150\n\t" //TODO
	    "        sbci r31,-1\n\t"
        "        ldi r18, 10\n\t"
        "        dec r19\n\t"
        "        brne rearr\n\t"
        ::
        [ps] "y" (ps),
        [pe] "z" (pe)
        : "r18", "r19", "r20", "r21", 
          "r22", "r23", "r24", "r25"
    );
}


void render(uint8_t *rgb_arr) {
    rearrange(rgb_arr);

    cli(); // TODO save interrupt enable state and restore

    uint8_t *p1  = &rgb_arr[1];
    uint8_t *p2  = &rgb_arr[241];
    uint8_t *p3  = &rgb_arr[481];
    uint8_t d1 = rgb_arr[0];
    uint8_t d2 = rgb_arr[240];
    uint8_t d3 = rgb_arr[480];

    const uint8_t mask = _BV(PB0) | _BV(PB1) | _BV(PB2);
    const uint8_t low = PORTB & (~mask);
    const uint8_t high = PORTB | mask;

    uint8_t nbits = 7;
    uint8_t tmp = low;
    uint16_t nbytes = 240;

    asm volatile(             
        "start:  nop\n\t"
        "        nop\n\t"
        "        nop\n\t"
        "set1:   out %[ioport], %[portdown]\n\t"
        "        lsl %[data1]\n\t"
        "        brcc a1\n\t"
        "        sbr %[tmp], %[bit1]\n\t"
        "a1:     lsl %[data2]\n\t"
        "        brcc a2\n\t"
        "        sbr %[tmp], %[bit2]\n\t"
        "a2:     out %[ioport], %[portup]\n\t"
        "        lsl %[data3]\n\t"
        "        brcc a3\n\t"
        "        sbr %[tmp], %[bit3]\n\t"
        "a3:     nop\n\t"
        "        dec %[bitcount]\n\t"
        "set0:   out %[ioport], %[tmp]           \n\t"
        "        mov %[tmp], %[portdown]\n\t"
        "        brne start\n\t"

        "        lsl %[data1]\n\t"
        "        brcc b1\n\t"
        "        sbr %[tmp], %[bit1]\n\t"
        "b1:     lsl %[data2]\n\t"
        "        out %[ioport], %[portdown]\n\t"
        "        brcc b2\n\t"
        "        sbr %[tmp], %[bit2]\n\t"
        "b2:     ld %[data1], %a[ptr1]+\n\t"
                 // ^^^
        "        ld %[data2], %a[ptr2]+\n\t"
                 // ^^^
        "        out %[ioport], %[portup]\n\t"
        "        lsl %[data3]\n\t"
        "        brcc b3\n\t"
        "        sbr %[tmp], %[bit3]\n\t"
        "b3:     ld %[data3], %a[ptr3]+\n\t"
                 // ^^^
        "        out %[ioport], %[tmp]          \n\t"
        "        ldi %[bitcount], 7\n\t"
        "        mov %[tmp], %[portdown]\n\t"
        "        sbiw %[bytecount], 1\n\t"
                 // ^^^
        "        brne set1\n\t"

        "        nop\n\t"
        "        out %[ioport], %[portdown]\n\t"
        ::
        [ioport]    "I" (_SFR_IO_ADDR(PORTB)),
        [portup]    "r" (high),
        [portdown]  "r" (low),
        [bitcount]  "d" (nbits),
        [ptr1]      "e" (p1),
        [ptr2]      "e" (p2),
        [ptr3]      "e" (p3),
        [data1]     "r" (d1),
        [data2]     "r" (d2),
        [data3]     "r" (d3),
        [bit1]      "I" (1 << PB0),
        [bit2]      "I" (1 << PB1),
        [bit3]      "I" (1 << PB2),
        [tmp]       "d" (tmp),
        [bytecount] "w" (nbytes)
    );
    sei(); // TODO
    
    rearrange(rgb_arr);
}

