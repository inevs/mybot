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

    enableSensor(ENA_RADLED);
    enableSensor(ENA_SCHRANKE);
    enableSensor(ENA_KANTLED);
    enableSensor(ENA_KLAPPLED);

    while(1) {
    	testDigitalSensor();
    }
    return 0;
}
