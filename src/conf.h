#ifndef _CONF_H_
#define _CONF_H_

#define NUM_RGB   (240)

#define OUT_PORT  (PORTB)
#define OUT_DR    (DDRB)
#define OUT_PIN_1 (PB0)
#define OUT_PIN_2 (PB1)
#define OUT_PIN_3 (PB2)


#define NUM_BYTES (NUM_RGB*3)

#define START_1   (0)
#define START_2   (NUM_BYTES/3)
#define START_3   (NUM_BYTES/3*2)

#endif
