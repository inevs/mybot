#include "maus.h"

#include <avr/io.h>
#include <util/delay.h>
#include "display.h"


#define SDIO PB6


void mouse_sendcmd(uint8_t cmd);	// Helper function
uint8_t getMouseReg(uint8_t reg);	// Helper function

/**
 * DESC:   Initialize optical mouse sensor 
 * PARAM:  None
 * RETURN: None
 **/
void mouseInit() {
	
	// Set pins
	DDRB |= (1<<PB7);
	PORTB &= ~(1<<PB7);
	
	mouse_sendcmd(0x00|0x80); // Config. register
	mouse_sendcmd(0x80); 	  // Reset command
	_delay_us(47);	
	mouse_sendcmd(0x00|0x80); // Config. register
	mouse_sendcmd(0x01);      // Normal operation
	_delay_us(47);
}

/**
 * DESC:   Send a instruction to mouse sensor 
 * PARAM:  8-bit value, represents the instruction
 * RETURN: None
 **/
void mouse_sendcmd(uint8_t cmd) {
	uint8_t i;
	
	DDRB |= (1<<SDIO); // Set SDIO as output
	
	// Shift out
	for(i=0;i<8;i++) {
		PORTB &= ~(1<<PB7); 	  // Clk low
		if( ((cmd>>7)&0x01) == 0) // Set data
			PORTB &= ~(1<<SDIO);
		else
			PORTB |= (1<<SDIO);
		cmd = cmd<<1;		
		PORTB |= (1<<PB7); // Clk high
	}	
}

/**
 * DESC:   Get x-direction movement of mouse sensor 
 * PARAM:  None
 * RETURN: 8-bit value, represents movement since last function call, could be between -127 and 128
 **/
int8_t readDX() {
	int8_t dx = (int8_t)getMouseReg(MOUSE_DX);
	return dx;
}

/**
 * DESC:   Get y-direction movement of mouse sensor 
 * PARAM:  None
 * RETURN: 8-bit value, represents movement since last function call, could be between -127 and 128
 **/
int8_t readDY() {
	int8_t dy = (int8_t)getMouseReg(MOUSE_DY);
	return dy;
}

/**
 * DESC:   Read a register from mouse sensor 
 * PARAM:  8-bit value, represents the register
 * RETURN: 8-bit value, represents register content
 **/
uint8_t getMouseReg(uint8_t reg) {
	uint8_t i=0;
	int8_t data=0;
	
	mouse_sendcmd(reg); // Register to read from
	
	_delay_us(100);
	
	DDRB &= ~(1<<SDIO);  	// Set SDIO as input
	PORTB &= ~(1<<SDIO); 	// No pullup
	for(i=0;i<8;i++) {
		PORTB &= ~(1<<PB7);	// Clk low for min. 250ns
		asm volatile("nop");
		asm volatile("nop");
		asm volatile("nop");
		data = data<<1; 
		PORTB |= (1<<PB7);	// Clk high			
		data |= ((PINB>>SDIO)&0x01); // Save bit
	}
	return data;	
}
