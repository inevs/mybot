#include <util/delay.h>

#include "tests.h"
#include "botlib.h"
#include "sensors.h"

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
	lcdSetCursor(0, 0);
	lcdPrintf("Hallo");
	lcdSetCursor(1, 0);
	lcdPrintf("mein Schatz");
	lcdSetCursor(2, 0);
	lcdPrintf("ich liebe dich");
	lcdSetCursor(3, 0);
	lcdPrintf("XOXOXOXO");
}

void testLichtSensoren() {
	lcdClear();
	lcdSetCursor(0, 0);
	lcdPrintf("Sensor LDRL: %d", getAnalog(LDRL));
	lcdSetCursor(1, 0);
	lcdPrintf("Sensor LDRR: %d", getAnalog(LDRR));
}

void testKantenSensoren() {
	lcdSetCursor(2, 0);
	lcdPrintf("Sensor KANTE_L: %d", getAnalog(KANTEL));
	lcdSetCursor(3, 0);
	lcdPrintf("Sensor KANTE_R: %d", getAnalog(KANTER));
	delay(10000);
}

void testAbstandsSensoren() {
	lcdSetCursor(1, 0);
	lcdPrintf("Abstand links: %d", getAnalog(ABSTL));
	lcdSetCursor(2, 0);
	lcdPrintf("Abstand rechts: %d", getAnalog(ABSTR));
	delay(10000);
}

void testLinienSensors() {
	lcdSetCursor(1, 0);
	lcdPrintf("Linie links: %d", getAnalog(LINEL));
	lcdSetCursor(2, 0);
	lcdPrintf("Linie rechts: %d", getAnalog(LINER));
	delay(10000);
}

void testAnalogSensors() {
	/*	uint8_t i;
	 for (i = 0; i < 8; i++) {
	 lcdClear();
	 lcdPrintf("Sensor %d: %d", i, getAnalog(i));
	 delay(10000);
	 }
	 */
}

void testDigitalSensors() {
	uint8_t i;
	for (i = 0; i < 30; i++) {
		lcdClear();
		lcdPrintf("Schranke: %d", getDigital(SCHRANKE));
		lcdSetCursor(1, 0);
		lcdPrintf("Klappe: %d", getDigital(KLAPPE));
		lcdSetCursor(2, 0);
		lcdPrintf("Rad l.: %d", getDigital(RADL));
		lcdSetCursor(3, 0);
		lcdPrintf("Rad r.: %d", getDigital(RADR));
		delay(1000);
	}
}

void testMouseSensor() {
	lcdClear();
	lcdSetCursor(0, 0);
	lcdPrintf("X: %d", readDX());
	lcdSetCursor(1, 0);
	lcdPrintf("Y: %d", readDY());
	delay(500);
}
