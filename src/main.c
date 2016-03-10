#include <avr/io.h>
#include <util/delay.h>

#include "botlib/botlib.h"
#include "botlib/tests.h"

void setup() {
	initLeds();
    initLcd();
    initSensors();
}

int main(void) {

    setup();

    while(1) {
        // testLED();
    	// testLCD();
    	testDigitalSensor();
    }
    return 0;
}
