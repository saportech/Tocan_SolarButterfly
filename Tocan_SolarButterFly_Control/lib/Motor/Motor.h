#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
public:
    Motor();
    void begin();
    void setOnOff(bool state);
    void setDirection(bool direction);
    void setSpeed(uint8_t speed); // Speed is 0-255

private:
    static const uint8_t MOTOR_ON_OFF = 14;
    static const uint8_t MOTOR_DIRECTION = 26;
    static const uint8_t MOTOR_SPEED = 5;
};

#endif
