#include <avr/io.h>
#include <util/delay.h>

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

// ISR (TIMER2_COMPA_vect) {
//      setLed(2);
//      toggleLED(1);
//      __builtin_avr_sei();
//  }


void setupTimer() {
    TCNT2 = 0x00;
    TCCR2A = 0x02; // CTC Mode
    TCCR2B = 0x03; // Prescaler 64
    OCR2A  = 100;

    TIMSK2 = 0x02;
    __builtin_avr_sei();
}

int main(void) {

    setup();
    // setupTimer();


    while(1) {
        setLed(3);
        delay(1000);
        clearLed(3);
        delay(1000);
    }
    
    return 0;
}
