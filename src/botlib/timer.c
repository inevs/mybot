#include <avr/interrupt.h>
#include "timer.h"
#include "led.h"

bool ledSet = false;
uint16_t count = 0;

void initTimer() {
    TCNT2 = 0x00;
    TCCR2A = _BV(WGM21);
    TCCR2B = _BV(CS22);
    OCR2A = ((XTAL/64/TIMER_2_CLOCK) - 1);

    TIMSK2 |= _BV(OCIE2A);
}

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
    if (++count > 5000) {
        toggleLED(LED_BLUE);
        count = 0;
    }
    sei();
}
