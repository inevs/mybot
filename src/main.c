#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "botlib/botlib.h"
#include "botlib/tests.h"

void setup() {
	initLeds();
    initLcd();
    initSensors();
    enableDigitalSensors();
    enableAnalogSensors();
    initTimer();
}

int main(void) {

    setup();
    sei();

    uint8_t val = ((XTAL/64/TIMER_2_CLOCK) - 1);

    while(1) {
        lcdPrintf("val = %d", val);
    }
    
    return 0;
}
