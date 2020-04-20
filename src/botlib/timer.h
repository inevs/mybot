#ifndef SRC_BOTLIB_TIMER_H_
#define SRC_BOTLIB_TIMER_H_

#include <avr/io.h>
#include <util/delay.h>
#include "defines.h"

#define F_CPU	16000000L	/*!< CPU-Frequenz [Hz] */
#define XTAL	F_CPU		/*!< CPU-Frequenz [Hz] */
#define TIMER_2_CLOCK 5619

void initTimer();

#endif //SRC_BOTLIB_TIMER_H_