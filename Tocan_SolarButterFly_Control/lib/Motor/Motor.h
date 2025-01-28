#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "OLED.h"

enum MotorOnOff {
    ON = LOW,
    OFF = HIGH
};

enum MotorDirection {
    FORWARD = HIGH,
    REVERSE = LOW
};

class Motor {
public:
    Motor();
    void begin();
    void setOnOff(bool state);
    void setDirection(bool direction);
    void setSpeed(int speed); // Speed is 0-255
    void runSpeeds();

    // Getters
    bool getOnOff() const;
    bool getDirection() const;
    int getSpeed() const;

private:
    static const int MOTOR_ON_OFF = 14;
    static const int MOTOR_DIRECTION = 26;
    static const int MOTOR_SPEED = 5;

    bool currentOnOffState;
    bool currentDirection;
    int currentSpeed;
};

#endif
