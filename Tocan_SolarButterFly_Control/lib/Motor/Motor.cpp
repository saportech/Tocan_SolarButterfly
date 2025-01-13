#include "Motor.h"

Motor::Motor() {}

void Motor::begin() {
    pinMode(MOTOR_ON_OFF, OUTPUT);
    pinMode(MOTOR_DIRECTION, OUTPUT);
    pinMode(MOTOR_SPEED, OUTPUT);

    digitalWrite(MOTOR_ON_OFF, HIGH);
    digitalWrite(MOTOR_DIRECTION, HIGH);
    ledcSetup(0, 5000, 8);
    ledcAttachPin(MOTOR_SPEED, 0);
    setSpeed(0);
}

void Motor::setOnOff(bool state) {
    digitalWrite(MOTOR_ON_OFF, state ? LOW : HIGH);
}

void Motor::setDirection(bool direction) {
    digitalWrite(MOTOR_DIRECTION, direction ? LOW : HIGH);
}

void Motor::setSpeed(uint8_t speed) {
    uint8_t pwmValue = map(speed, 1, 5, 51, 255);
    ledcWrite(0, pwmValue);
}
