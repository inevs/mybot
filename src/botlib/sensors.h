#ifndef SRC_BOTLIB_SENSORS_H_
#define SRC_BOTLIB_SENSORS_H_
#include <avr/io.h>

typedef enum { ABSTAND=0, ENA_RADLED, ENA_SCHRANKE, ENA_KANTLED, ENA_KLAPPLED, MAUS, ERW1, ERW2 } SENSORTYPE;
typedef enum  { ABSTL=0, ABSTR, LINEL, LINER, LDRL, LDRR, KANTEL, KANTER, VOLTAGE, CURRENT } SENSOR_ANALOG;
#define SCHRANKE PB0
#define RADL PB4
#define KLAPPE PD6
#define RADR PD3
#define SENSOR_DIGITAL uint8_t

void initSensors();
void disableSensor(SENSORTYPE id);
void enableSensor(SENSORTYPE id);
uint16_t getAnalog(SENSOR_ANALOG id);
uint8_t getDigital(SENSOR_DIGITAL id);

#endif
