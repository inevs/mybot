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

    int8_t speedInc = 10;
    int8_t leftSpeed = 0;
    int8_t rightSpeed = 0;
    uint16_t command = 0x0;
    bool toggle = 0;

    setup();
    sei();
    setSpeed(leftSpeed, rightSpeed);

    while(1) {
        command = getRC5Cmd();
        lcdSetCursor(0, 0); lcdPrintf("Command = %d", command);
        lcdSetCursor(1, 0); lcdPrintf("Address = %d", getRC5Addr());
        lcdSetCursor(2, 0); lcdPrintf("rc5toggle = %d", getRC5Toggle());
        lcdSetCursor(3, 0); lcdPrintf("l = %d r = %d", leftSpeed, rightSpeed);
        delay(1000);

        if (toggle != getRC5Toggle()) {
            toggle = getRC5Toggle();
            if (command == 21) {
                leftSpeed += speedInc;
                rightSpeed += speedInc;
            }
            if (command == 20) {
                leftSpeed -= speedInc;
                rightSpeed -= speedInc;
            }
            if (command == 16) {
                rightSpeed += speedInc;
            }
            if (command == 17) {
                leftSpeed += speedInc;
            }
            if (command == 17) {
                leftSpeed = 0;
                rightSpeed = 0;
            }
            setSpeed(leftSpeed, rightSpeed);
        }
    }
    
    return 0;
}
