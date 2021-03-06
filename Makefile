DEVICE     = atmega1284p
CLOCK      = 16000000
PROGRAMMER = -c avrispv2 -P usb
OBJECTS    = src/main.o \
			 src/botlib/shift.o \
			 src/botlib/led.o \
			 src/botlib/display.o \
			 src/botlib/sensors.o \
			 src/botlib/maus.o \
			 src/botlib/tests.o \
			 src/botlib/timer.o \
			 src/botlib/motor.o

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

test-analog:
	$(AVRDUDE) -U flash:w:test-bin/ct-Bot-analog.hex:i

test-digital:
	$(AVRDUDE) -U flash:w:test-bin/ct-Bot-digital.hex:i

test-motor:
	$(AVRDUDE) -U flash:w:test-bin/ct-Bot-motor.hex:i

load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c
