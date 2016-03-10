#include "shift.h"

#define SDI			PC0
#define IC6_SRCLK	PC4
#define IC6_RCLK	PC1
#define IC5_SRCLK	PC3
#define IC5_RCLK	PC1

void shiftData(uint8_t data, uint8_t srclk, uint8_t rclk);

void shiftLED(uint8_t data) {
	shiftData(data, IC6_SRCLK, IC6_RCLK);
}

void shiftSensors(uint8_t data) {
	shiftData(data, IC5_SRCLK, IC5_RCLK);
}

void shiftData(uint8_t data, uint8_t srclk, uint8_t rclk) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		if (((data >> 7) & 0x01) == 1)
			PORTC |= (1 << SDI);
		else
			PORTC &= ~(1 << SDI);

		PORTC |= (1 << srclk);
		data = data << 1;
		PORTC &= ~(1 << srclk);
	}
	PORTC |= (1 << rclk);
	asm volatile ("nop");
	PORTC &= ~(1 << rclk);
}



