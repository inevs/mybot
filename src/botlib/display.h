#ifndef SRC_BOTLIB_DISPLAY_H_
#define SRC_BOTLIB_DISPLAY_H_

#include <avr/io.h>

void initLcd();
void lcdSetCursor(uint8_t row, uint8_t pos);
void lcdPrintf(const char *s, ...);
void lcdClear();


#endif
