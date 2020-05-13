#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum {
    left,
    right
} Motor;

typedef enum {
    forward,
    backward
} MotorDirection;

void motorInit();
void setMotorSpeed(Motor motor, int8_t power);

#endif