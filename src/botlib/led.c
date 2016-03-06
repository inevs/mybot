#include "led.h"
#include "shift.h"

uint8_t led_status;

void initLeds() {
	// Set outputs for SDI, register RCLK, SRCLK
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC4);
	led_status = 0x00;
	shiftLED(led_status);
}

void setLed(uint8_t nr) {
	led_status |= nr;
	shiftLED(led_status);
}

void clearLed(uint8_t nr) {
	led_status &= ~nr;
	shiftLED(led_status);
}

