#include <avr/interrupt.h>
#include "timer.h"
#include "led.h"

bool ledSet = false;
uint16_t count = 0;

void initTimer() {
    TCNT2 = 0x00;
    TCCR2A = _BV(WGM21); // CTC Mode
    TCCR2B = _BV(CS22);  // 64 Prescaler
    // timerclock = 16.000.000 / 64 = 250.000
    OCR2A = (25 - 1); // ISR call every 100µs

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

// is called every 100µs
ISR (TIMER2_COMPA_vect) {
    if (++count > 10000) {
        toggleLED(LED_BLUE);
        count = 0;
    }
    sei();
}
