#include <avr/io.h>
#include "motor.h"

uint8_t g_motorMaxPower;
uint8_t g_motorMinPower;

void motor_enable() {
	TCCR1B |= (1<<CS10);
}

void motorInit() {
	// Set pins
	DDRC |= (1<<PC6) | (1<<PC7);
	DDRD |= (1<<PD4) | (1<<PD5);
	
	TCCR1A |= (1<<COM1A1) | (1<<COM1B1);	// Clear OC1A/OC1B on Compare, set at BOTTOM
	TCCR1A |= (1<<WGM12) | (1<<WGM10);		// 8-Bit Fast PWM

	// Set compare registers
	OCR1AL = 20;
	OCR1BL = 20;
	
	// Set min. and max. pwm value
	g_motorMaxPower = 255;
	g_motorMinPower = 0;
	
	motor_enable(); // Enable the motor timer
}

void setMotorDirection(Motor motor, MotorDirection direction) {
	if (motor == left) {
		if (direction == forward) {
			PORTC |= (1<<PC6);
        } else {
			PORTC &= ~(1<<PC6);
        }
	} else if (motor == right) {
		if (direction == forward) {
			PORTC &= ~(1<<PC7);
        } else {
			PORTC |= (1<<PC7);
        }
	}
}

void setMotorSpeed(Motor motor, int8_t speed) {
	if (speed < 0) {
		setMotorDirection(motor, backward);
		speed *= -1;
	} else if (speed > 0) {
		setMotorDirection(motor, forward);
    }
	
	if (motor == left) {
		OCR1AL = g_motorMinPower + ((uint16_t)(g_motorMaxPower - g_motorMinPower) * speed / 100);
	} else if (motor == right) {
		OCR1BL = g_motorMinPower + ((uint16_t)(g_motorMaxPower - g_motorMinPower) * speed / 100);
	}

	if (speed > 0) {
		motor_enable();
    }
}