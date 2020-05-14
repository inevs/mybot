#include <avr/interrupt.h>
#include "timer.h"
#include "rc5.h"

void initRC5() {
    DDRB &= ~(1 << FERNBED);
}

void initTimer() {
    TCNT2 = 0x00;
    TCCR2A = _BV(WGM21); // CTC Mode
    TCCR2B = _BV(CS22);  // 64 Prescaler
    // timerclock = 16.000.000 / 64 = 250.000
    OCR2A = (25 - 1); // ISR call every 100µs

    TIMSK2 |= _BV(OCIE2A);

    initRC5();
}

void decodeRC5() {
	if(++g_rc5ImpulseCount > RC5_PULSE_MAX) {
		if(g_rc5receive & 0x2000) {			// Code valid?
			g_rc5code = g_rc5receive;
			g_rc5toggle = g_rc5receive >> 11 & 0x01;
		}
		g_rc5receive = 0;
	}
	if( (g_rc5lastlevel ^ PINB) & (1 << PB1) ) {	// Pinchange on PINB1
		g_rc5lastlevel = ~g_rc5lastlevel;
		
		if(g_rc5ImpulseCount < RC5_PULSE_MIN) {	
			g_rc5receive = 0;
		}
		
		if(!g_rc5receive || g_rc5ImpulseCount > RC5_PULSE_1_2) {
			g_rc5receive = g_rc5receive<<1;
			if( !(g_rc5lastlevel & (1 << PB1)) )
				g_rc5receive |= 1;
			g_rc5ImpulseCount = 0;
		}
	}
}

// is called every 100µs
ISR (TIMER2_COMPA_vect) {
    decodeRC5();
    sei();
}
