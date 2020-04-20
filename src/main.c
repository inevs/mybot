#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "botlib/botlib.h"
#include "botlib/tests.h"

#define F_CPU	16000000L	/*!< CPU-Frequenz [Hz] */
#define XTAL	F_CPU		/*!< CPU-Frequenz [Hz] */
#define TIMER_2_CLOCK 5619

void setup() {
	initLeds();
    initLcd();
    initSensors();
    enableDigitalSensors();
    enableAnalogSensors();
    initTimer();
}

bool ledSet = false;

void toggleLED(uint8_t nr) {
    if (ledSet) {
        clearLed(nr);
        ledSet = false;
    } else {
        setLed(nr);
        ledSet = true;
    }
    delay(1000);
}

ISR (TIMER2_COMPA_vect) {
    toggleLED(LED_BLUE);
    sei();
 }


void setupTimer() {
    TCCR2A = 0x42;
    TCCR2B = 0x05;
    TCNT2 = 0;
    OCR2A = 240;

    TIMSK2 = 0x02;
}

int main(void) {

    setup();
    setupTimer();

    sei();

    while(1) {      
    }
    
    return 0;
}
