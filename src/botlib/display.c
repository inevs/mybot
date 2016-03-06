#include <util/delay.h>
#include <stdio.h>
#include "display.h"
#include "shift.h"

void lcdsendcmd(char cmd);
void lcdsenddata(char data);
void lcdSend(char data, int mode);

#define MODE_COMMAND 0
#define MODE_DATA 1

void lcdInit() {
	// Set outputs for SDI, register RCLK, SRCLK
	DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);

	_delay_ms(15);
	_delay_ms(15);
	_delay_ms(11);

	lcdsendcmd(0x38);	// 2-line mode, 5x8pixel per character
	_delay_us(40);		// Sleep 40µs
	lcdsendcmd(0x0C);	// Disply off
	_delay_us(40);		// Sleep 4µs
	lcdsendcmd(0x01);	// Display clear
	_delay_ms(1.5);		// Sleep 1.5ms
	lcdsendcmd(0x06);	// EntryMode increment, entire shift off
	_delay_ms(1.5);		// Sleep 1.5ms
}

void lcdSetCursor(uint8_t row, uint8_t pos) {
	if(row==0) {
		lcdsendcmd(0x80+pos); // DDRAM Adress 00
	}
	else if(row==1) {
		lcdsendcmd(0xC0+pos); // DDRAM Adress 40
	}
	else if(row==2) {
		lcdsendcmd(0x94+pos); // DDRAM Adress 14
	}
	else if(row==3) {
		lcdsendcmd(0xD4+pos); // DDRAM Adress 54
	}
}

void lcdPrintf(const char *s, ...) {
	char buffer[20]; // max. one row
	uint8_t i=0;
	va_list args;

	va_start(args, s); // Initialize va_list args
	vsnprintf(buffer,20,s,args); // Format output
	va_end(args);

	// Print each character
	while(buffer[i] != '\0') {
		lcdsenddata(buffer[i]);
		i++;
	}
}

void lcdClear() {
	lcdsendcmd(0x01); 	// Display clear
	_delay_ms(20);
}

void lcdsendcmd(char cmd) {
	lcdSend(cmd, MODE_COMMAND);
}

void lcdsenddata(char data) {
	lcdSend(data, MODE_DATA);
}

void lcdSend(char data, int mode) {
	PORTC &= ~(1 << PC2);	// Deactivate display (Enable=0)
	PORTC &= ~(1 << PC0);	// Instruction mode (RS=0)
	PORTC &= ~(1 << PC1);	// Write mode (R/W=0)

	uint8_t i;

	for (i = 0; i < 8; i++) {
		if (((data >> 7) & 0x01) == 1)
			PORTC |= (1 << PC0);
		else
			PORTC &= ~(1 << PC0);
		PORTC |= (1 << PC1);
		data = data << 1;
		PORTC &= ~(1 << PC1);
	}
	PORTC &= ~(1 << PC0);	// RS = 0

	PORTC |= (1 << PC2); // Activate display (Enable=1)
	if (mode == 1) {
		PORTC |= (1 << PC0);  // Data mode (RS=0)
	}
	PORTC &= ~(1 << PC1); // Write mode (R/W=0)
	PORTC &= ~(1 << PC2);	// Deactivate display (Enable=0)
	_delay_us(40);
}
