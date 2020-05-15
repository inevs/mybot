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
    initMotor();
}

int main(void) {

    setup();
    sei();

    while(1) {
        testInfrared();
    }
    
    return 0;
}
