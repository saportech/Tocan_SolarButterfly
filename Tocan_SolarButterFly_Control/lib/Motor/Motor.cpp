#include "Motor.h"

Motor::Motor() : currentOnOffState(OFF), currentDirection(FORWARD), currentSpeed(0) {}

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
    digitalWrite(MOTOR_ON_OFF, state ? HIGH : LOW);
    currentOnOffState = state;
}

void Motor::setDirection(bool direction) {
    digitalWrite(MOTOR_DIRECTION, direction ? HIGH : LOW);
    currentDirection = direction;
}

void Motor::setSpeed(int speed) {
    switch (speed) {
        case 5:
            ledcWrite(0, 62);
            break;
        case 4:
            ledcWrite(0, 73);
            break;
        case 3:
            ledcWrite(0, 76);
            break;
        case 2:
            ledcWrite(0, 78);
            break;
        case 1:
            ledcWrite(0, 81);
            break;
        case 0:
            ledcWrite(0, 100);
            break;
        default:
            Serial.println("Invalid PWM value");
            return; // Exit if the value is invalid
    }
    currentSpeed = speed;
}

void Motor::runSpeeds() {
    for (int i = 74; i <= 90; i++) {
        ledcWrite(0, i);
        //Serial.println(i);
        currentSpeed = i;
        delay(50);
    }
}

bool Motor::getOnOff() const {
    return currentOnOffState;
}

bool Motor::getDirection() const {
    return currentDirection;
}

int Motor::getSpeed() const {
    return currentSpeed;
}
