#ifndef SRC_BOTLIB_MAUS_H_
#define SRC_BOTLIB_MAUS_H_

#include <avr/io.h>

#define MOUSE_CONF	0x00	// Config-Register
#define MOUSE_STATE	0x01	// Status-Register
#define MOUSE_DY 	0x02	// Delta-Y Register
#define MOUSE_DX	0x03	// Delta-X Register
#define MOUSE_SQUAL	0x04	// SQUAL-Register
#define MOUSE_MAX	0x05	// Max. Pixel
#define	MOUSE_MIN	0x06	// Min. Pixel
#define MOUSE_PXLS	0x07	// Pixelsumme
#define MOUSE_PXLD	0x08	// Pixel-Daten
#define MOUSE_SUP	0x09	// Shutter-Register High
#define MOUSE_SLOW	0x0A	// Shutter-Register Low
#define MOUSE_INV	0x11	// Maus-ID Register

void mouseInit(void);
int8_t readDY(void);
int8_t readDX(void);
uint8_t getMouseReg(uint8_t reg);

#endif
