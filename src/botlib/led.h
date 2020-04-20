#ifndef SRC_BOTLIB_LED_H_
#define SRC_BOTLIB_LED_H_

#include <avr/io.h>

void initLeds();
void setLed(uint8_t nr);
void clearLed(uint8_t nr);

#define LED_RIGHT   0
#define LED_LEFT    1
#define LED_RED     2
#define LED_ORANGE  3
#define LED_YELLOW  4
#define LED_GREEN1  5
#define LED_BLUE    6
#define LED_WHITE   7

#endif
