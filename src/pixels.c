#include <avr/interrupt.h>
#include "pixels.h"

#define START_1   (0)
#define START_2   (NUM_BYTES/3)
#define START_3   (NUM_BYTES/3*2)


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


void init_pixels(void) {
    OUT_DR |= (1 << OUT_PIN_1);
    OUT_DR |= (1 << OUT_PIN_2);
    OUT_DR |= (1 << OUT_PIN_3);
    OUT_PORT &= ~(1 << OUT_PIN_1);
    OUT_PORT &= ~(1 << OUT_PIN_2);
    OUT_PORT &= ~(1 << OUT_PIN_3);
}


void render(uint8_t *rgb_arr) {
    rearrange(rgb_arr);
    
    uint8_t tmp_sreg = SREG;

    uint8_t *p1 = &rgb_arr[START_1];
    uint8_t *p2 = &rgb_arr[START_2];
    uint8_t *p3 = &rgb_arr[START_3];
    uint8_t d1 = *p1++;
    uint8_t d2 = *p2++;
    uint8_t d3 = *p3++;

    const uint8_t mask = _BV(OUT_PIN_1) | _BV(OUT_PIN_2) | _BV(OUT_PIN_3);
    const uint8_t low = OUT_PORT & (~mask);
    const uint8_t high = OUT_PORT | mask;

    uint8_t nbits = 7;
    uint8_t tmp = low;
    uint16_t nbytes = NUM_BYTES/3;

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
        [ioport]    "I" (_SFR_IO_ADDR(OUT_PORT)),
        [portup]    "l" (high),
        [portdown]  "l" (low),
        [bitcount]  "d" (nbits),
        [ptr1]      "e" (p1),
        [ptr2]      "e" (p2),
        [ptr3]      "e" (p3),
        [data1]     "d" (d1),
        [data2]     "d" (d2),
        [data3]     "d" (d3),
        [bit1]      "I" (1 << OUT_PIN_1),
        [bit2]      "I" (1 << OUT_PIN_2),
        [bit3]      "I" (1 << OUT_PIN_3),
        [tmp]       "d" (tmp),
        [bytecount] "w" (nbytes)
    );
    
    SREG = tmp_sreg;
    
    rearrange(rgb_arr);
}

