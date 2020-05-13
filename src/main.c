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
    motorInit();
    setMotorSpeed(left, 0);
    setMotorSpeed(right, 0);

    while(1) {
       lcdSetCursor(0, 0); lcdPrintf("Command = %d", getRC5Cmd());
       lcdSetCursor(1, 0); lcdPrintf("Address = %d", getRC5Addr());
       lcdSetCursor(2, 0); lcdPrintf("rc5toggle = %d", getRC5Toggle());
       delay(1000);
    }
    
    return 0;
}
