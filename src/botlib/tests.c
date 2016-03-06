#include <util/delay.h>

#include "tests.h"
#include "botlib.h"

void delay(int time) {
	_delay_ms(100);
}

void testLED(void) {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		setLed((1 << i));
		delay(5000);
		clearLed((1 << i));
		delay(5000);
	}
}

void testLCD(void) {
    lcdInit();

    lcdSetCursor(0, 0);
    lcdPrintf("Hallo");
    lcdSetCursor(1, 0);
    lcdPrintf("mein Schatz");
    lcdSetCursor(2, 0);
    lcdPrintf("ich liebe dich");
    lcdSetCursor(3, 0);
    lcdPrintf("XOXOXOXO");



//	uint8_t i;
//	for (i = 0; i < 4; i++) {
//		lcdClear();
//		lcdSetCursor(i, i);
//		lcdPrintf("Test %d, 0x%x, %.2f", i, i, (float) i);
//		delay(10000);
//	}
}

