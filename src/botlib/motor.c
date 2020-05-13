#include <avr/io.h>
#include "motor.h"

uint8_t g_motorMaxPower;
uint8_t g_motorMinPower;

void motor_enable() {
	TCCR1B |= (1<<CS10);
}

void initMotor() {
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

void setSpeed(int8_t leftSpeed, int8_t rightSpeed) {
    if (leftSpeed < 0) {
        setMotorDirection(left, backward);
        leftSpeed *= -1;
    } else {
        setMotorDirection(left, forward);
    }

    if (rightSpeed < 0) {
        setMotorDirection(right, backward);
        rightSpeed *= -1;
    } else {
        setMotorDirection(right, forward);
    }

	OCR1AL = g_motorMinPower + ((uint16_t)(g_motorMaxPower - g_motorMinPower) * leftSpeed / 100);
	OCR1BL = g_motorMinPower + ((uint16_t)(g_motorMaxPower - g_motorMinPower) * rightSpeed / 100);
}