#ifndef SRC_BOTLIB_LED_H_
#define SRC_BOTLIB_LED_H_

#include <avr/io.h>

void initLeds();
void setLed(uint8_t nr);
void clearLed(uint8_t nr);

#define LED1 1
#define LED2 2
#define LED3 4
#define LED4 8
#define LED5 16
#define LED6 32
#define LED7 64
#define LED8 128




#endif
