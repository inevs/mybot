#include <util/delay.h>

#include "tests.h"
#include "botlib.h"
#include "sensors.h"

void delay(int time) {
	_delay_ms(100);
}

void testLED(void) {
	lcdSetCursor(0, 0);
	lcdPrintf("test LED");

	uint8_t i;
	for (i = 0; i < 8; i++) {
		setLed(i);
		delay(5000);
		clearLed(i);
		delay(5000);
	}
}

void testLCD(void) {
	lcdSetCursor(0, 0);
	lcdPrintf("Hallo Sven!");
	lcdSetCursor(1, 0);
	lcdPrintf("Gratuliere");
	lcdSetCursor(2, 0);
	lcdPrintf("Das Display scheint");
	lcdSetCursor(3, 0);
	lcdPrintf("zu funktionieren");
}

void testLichtSensoren() {
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
}

void testAbstandsSensoren() {
	lcdSetCursor(1, 0);
	lcdPrintf("Abstand links: %d", getAnalog(ABSTL));
	lcdSetCursor(2, 0);
	lcdPrintf("Abstand rechts: %d", getAnalog(ABSTR));
//	delay(10000);
}

void testLinienSensors() {
	lcdSetCursor(1, 0);
	lcdPrintf("Linie links: %d", getAnalog(LINEL));
	lcdSetCursor(2, 0);
	lcdPrintf("Linie rechts: %d", getAnalog(LINER));
//	delay(10000);
}

void testAnalogSensors() {
	uint8_t i;
	for (i = 0; i < 8; i++) {
		lcdClear();
		lcdPrintf("Sensor %d: %d", i, getAnalog(i));
		delay(10000);
	}
}

void testDigitalSensors() {
	uint8_t i;
	lcdPrintf("Schranke: %d", getDigital(SCHRANKE));
	lcdSetCursor(1, 0);
	lcdPrintf("Klappe: %d", getDigital(KLAPPE));
	lcdSetCursor(2, 0);
	lcdPrintf("Rad l.: %d", getDigital(RADL));
	lcdSetCursor(3, 0);
	lcdPrintf("Rad r.: %d", getDigital(RADR));
//	delay(1000);
}

void testMouseSensor() {
	lcdSetCursor(0, 0);
	lcdPrintf("X: %d", readDX());
	lcdSetCursor(1, 0);
	lcdPrintf("Y: %d", readDY());
//	delay(500);
}

void testInfrared() {
	lcdSetCursor(0, 0); lcdPrintf("Command = %d", getRC5Cmd());
	lcdSetCursor(1, 0); lcdPrintf("Address = %d", getRC5Addr());
	lcdSetCursor(2, 0); lcdPrintf("rc5toggle = %d", getRC5Toggle());
//	delay(1000);	
}

void testAll() {
	lcdClear();
	switch (getRC5Cmd()) {
	case 1:
		testLCD();
		break;
	case 2:
		testLED();
		break;
	case 3:
		testLichtSensoren();
		break;
	case 4:
		testKantenSensoren();
		break;
	case 5:
		testAbstandsSensoren();
		break;
	case 6:
		testLinienSensors();
		break;
	case 7:
		testAnalogSensors();
		break;
	case 8:
		testDigitalSensors();
		break;
	case 9:
		testMouseSensor();
		break;
	default:
		testInfrared();
		break;
	}
	delay(10000);
}