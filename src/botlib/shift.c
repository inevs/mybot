#include "shift.h"

#define SDI			PC0
#define IC4_SRCLK	PC4
#define IC4_RCLK	PC1

void shiftData(uint8_t data, uint8_t srclk, uint8_t rclk);


void shiftLED(uint8_t data) {
	shiftData(data, IC4_SRCLK, IC4_RCLK);
}

void shiftData(uint8_t value, uint8_t srclk, uint8_t rclk) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		if (((value >> 7) & 0x01) == 1)
			PORTC |= (1 << SDI);
		else
			PORTC &= ~(1 << SDI);

		PORTC |= (1 << srclk);
		value = value << 1;
		PORTC &= ~(1 << srclk);
	}
	PORTC |= (1 << rclk);
	asm volatile ("nop");
	PORTC &= ~(1 << rclk);
}




