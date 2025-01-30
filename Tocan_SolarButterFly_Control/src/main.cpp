#include <Arduino.h>
#include "ComControl.h"
#include "Motor.h"
#include "OLED.h"

ComControl comControl;
Motor motor;
OLED oled;

#define SOLAR_SENSITIVITY_PIN 33

float filteredValue = 0.0;
const float alpha = 0.1;

float sampleAndFilter();
void displayMotorStatus(int mappedValue);

void setup() {
    Serial.begin(115200);
    Serial.println("Control ESP32 Ready");
    comControl.begin();
    motor.begin();
    oled.begin();

    filteredValue = analogRead(SOLAR_SENSITIVITY_PIN); // Initialize filter
}

void loop() {

    static int previousValue = -2; // Tracks the previous value
    static unsigned long lastSendTime = 0;
    const unsigned long SEND_INTERVAL = 100;

    filteredValue = sampleAndFilter();

    int solarPanelsActivated = comControl.checkInput();
    //Serial.println("Solar Panels Activated: " + String(solarPanelsActivated));

    if (solarPanelsActivated <= 0) {
        motor.setOnOff(OFF);
        motor.setSpeed(0);
        if (previousValue > 0) {
            Serial.println("Motor turned OFF and speed set to 0");
        }
    } else if (solarPanelsActivated > 0) {
        if (previousValue <= 0) {
            motor.setOnOff(ON);
            motor.setSpeed(solarPanelsActivated);
            Serial.println("Motor turned ON and speed set to: " + String(solarPanelsActivated));
        } else if (solarPanelsActivated != previousValue) {
            motor.setSpeed(solarPanelsActivated);
            Serial.println("Motor speed updated to: " + String(solarPanelsActivated));
        }
    }
    previousValue = solarPanelsActivated;

    if (millis() - lastSendTime >= SEND_INTERVAL) {
        int mappedValue = map(filteredValue, 0, 4095, 0, 4000);
        comControl.sendMessage(mappedValue);
        displayMotorStatus(mappedValue);
        lastSendTime = millis();
    }
}

float sampleAndFilter() {
    static unsigned long lastSample = millis();
    const unsigned long SAMPLE_INTERVAL = 10;

    if (millis() - lastSample >= SAMPLE_INTERVAL) {
        int rawValue = analogRead(SOLAR_SENSITIVITY_PIN);
        filteredValue = (alpha * rawValue) + ((1 - alpha) * filteredValue);
        lastSample = millis();
    }

    return filteredValue;
}

void displayMotorStatus(int mappedValue) {
    bool motorState = motor.getOnOff();
    bool motorDirection = motor.getDirection();
    int motorSpeed = motor.getSpeed();

    String status = "State: " + String(motorState ? "OFF" : "ON") + "\n";
    status += "Dir: " + String(motorDirection ? "FWD" : "REV") + "\n";
    status += "Speed: " + String(motorSpeed) + "\n";
    status += "Threshold: " + String(mappedValue);

    oled.write(status);
}
