#include "Motor.h"

Motor::Motor() : currentOnOffState(OFF), currentDirection(FORWARD), currentSpeed(0) {}

void Motor::begin() {
    pinMode(MOTOR_ON_OFF, OUTPUT);
    pinMode(MOTOR_DIRECTION, OUTPUT);
    pinMode(MOTOR_SPEED, OUTPUT);

    digitalWrite(MOTOR_ON_OFF, HIGH);
    digitalWrite(MOTOR_DIRECTION, HIGH);
    ledcSetup(0, 30000, 10);
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
            ledcWrite(0, 0);
            break;
        case 4:
            ledcWrite(0, 7);
            break;
        case 3:
            ledcWrite(0, 56);
            break;
        case 2:
            ledcWrite(0, 309);
            break;
        case 1:
            ledcWrite(0, 561);
            break;
        case 0:
            ledcWrite(0, 1023);
            break;
        default:
            Serial.println("Invalid PWM value");
            return; // Exit if the value is invalid
    }
    currentSpeed = speed;
}

void Motor::runSpeeds() {
    for (int i = 6; i <= 7; i++) {
        ledcWrite(0, i);
        Serial.println(i);
        currentSpeed = i;
        delay(3000);
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
