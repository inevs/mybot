#include <util/delay.h>

#include "tests.h"
#include "botlib.h"

void delay(int time) {
	_delay_ms(100);
}

void testLED(void) {
	uint8_t i;
	for(i=0;i<8;i++) {
		setLed((1<<i));
		delay(5000);
		clearLed((1<<i));
		delay(5000);
	}
}



