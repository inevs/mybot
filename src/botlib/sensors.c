#include <avr/io.h>
#include "sensors.h"
#include "shift.h"

uint8_t sensorState;
void initADC();

void initSensors() {
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC3);
	DDRA = 0x00;
	PORTA = 0x00;

	sensorState = 0xFF;
	shiftSensors(sensorState);

	initADC();
}

void initADC() {
	// ADC
	ADMUX = 0x40; // VCC as Vref
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128x Prescaler

	uint8_t i;
	for (i = 0; i < 2; i++) {
		ADCSRA |= (1 << ADSC); // Start Conversion
		while ((ADCSRA & (1 << ADSC)) != 0)
			; // Wait for finish
	}
}

void disableSensor(SENSORTYPE id) {
	sensorState |= (1 << id);
	shiftSensors(sensorState);
}

void enableSensor(SENSORTYPE id) {
	sensorState &= ~(1 << id);
	shiftSensors(sensorState);
}

void enableDigitalSensors() {
    enableSensor(ENA_RADLED);
    enableSensor(ENA_SCHRANKE);
    enableSensor(ENA_KLAPPLED);
}

void enableAnalogSensors() {
	enableSensor(ENA_KANTLED);
	enableSensor(ENA_ABSTAND);
	enableSensor(ENA_MAUS);
}

uint16_t getAnalog(SENSOR_ANALOG id) {
	uint16_t ret = 0;

	ADMUX = 0x40 | id; 	// Set input
	ADCSRA |= (1 << ADSC); 	// Start conversion
	while ((ADCSRA & (1 << ADSC)) != 0)
		;
	ret = ADCL | (ADCH << 8);
	return ret;
}

uint8_t getDigital(SENSOR_DIGITAL id) {
	if(id == KLAPPE || id == RADR)
		return (PIND&(1<<id))>>id;
	else
		return (PINB&(1<<id))>>id;
}

