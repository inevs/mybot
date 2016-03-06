#include "led.h"

uint8_t led_status;
void ledshift(uint8_t value);

void initLeds() {
	// Set outputs for SDI, register RCLK, SRCLK
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC4);
	led_status = 0x00;
	ledshift(led_status);
}

void setLed(uint8_t nr) {
	led_status |= nr;
	ledshift(led_status);
}

void clearLed(uint8_t nr) {
	led_status &= ~nr;
	ledshift(led_status);
}

void ledshift(uint8_t value) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		if (((value >> 7) & 0x01) == 1)
			PORTC |= (1 << PC0);
		else
			PORTC &= ~(1 << PC0);

		PORTC |= (1 << PC4);
		value = value << 1;
		PORTC &= ~(1 << PC4);
	}
	PORTC |= (1 << PC1);
	asm volatile ("nop");
	PORTC &= ~(1 << PC1);
}

