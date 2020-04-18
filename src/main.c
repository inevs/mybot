#include <avr/io.h>
#include <util/delay.h>

#include "botlib/botlib.h"
#include "botlib/tests.h"

void setup() {
	initLeds();
    initLcd();
    initSensors();
    enableDigitalSensors();
    enableAnalogSensors();
}

int main(void) {

    setup();

    while(1) {
    	testLED();
    }
    return 0;
}
