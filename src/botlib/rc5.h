#ifndef RC5_H_
#define RC5_H_

#define RC5_PULSE_MAX 20
#define RC5_PULSE_MIN 4
#define RC5_PULSE_1_2 12

// Macros
#define getRC5Cmd() (g_rc5code&0x003F)
#define getRC5Addr() ((g_rc5code&0x07C0)>>6)
#define getRC5Toggle() (g_rc5toggle)
#define clearRC5Toggle() (g_rc5toggle = -1)
#define clearRC5Code() (g_rc5code = 0)

uint8_t g_rc5lastlevel;	// last pin value (high or low)
uint8_t g_rc5timer; 	// timer vor timeout
uint16_t g_rc5tmp; 		// temp for receiving
uint16_t g_rc5code;		// complete rc5 string
int8_t g_rc5toggle;		// toggle bit

#endif /*RC5_H_*/
