# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.

VERSION=0.0.1
TARGET=ledpix
MCU=atmega328p
DF_CPU=16000000
CCONF=-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS=-c -mmcu=$(MCU) -DF_CPU=$(DF_CPU) -Os $(CCONF) -Wall -Wstrict-prototypes
LDFLAGS=-mmcu=$(MCU) -Wall

PROGRAMMER=avrisp
PORT=-P/dev/ttyACM0
BAUD=-b 19200


SOURCES=pixels.c main.c


OBJECTS=$(SOURCES:.c=.o)


all: hex

hex: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(OBJECTS)
	avr-gcc $(LDFLAGS) $(OBJECTS) -o $(TARGET).elf

.c.o:
	avr-gcc $(CFLAGS) $< -o $@

size:
	avr-size --mcu=$(MCU) -C $(TARGET).elf
 
program:
	avrdude -p$(MCU) $(PORT) $(BAUD) -c$(PROGRAMMER) -Uflash:w:$(TARGET).hex:a

clean_tmp:
	rm -rf *.o
	rm -rf *.elf

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex

.PHONY: clean clean_tmp
