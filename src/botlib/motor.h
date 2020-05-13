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

void initMotor();
void setSpeed(int8_t left, int8_t right);

#endif