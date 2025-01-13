#include <Arduino.h>
#include "ComControl.h"
#include "Motor.h"

ComControl comControl;
Motor motor;

// Function Declaration
void sendAnalogData();

void setup() {
    Serial.begin(115200);
    Serial.println("Control ESP32 Ready");
    comControl.begin();
    pinMode(33, INPUT); // Analog input pin
}

void loop() {
    static unsigned long lastSendTime = 0;
    const unsigned long SEND_INTERVAL = 1000; // Send data every 1 second

    // Handle solar panel activation
    int solarPanelsActivated = comControl.checkInput();
    if (solarPanelsActivated > 0) {
        Serial.println("Solar panels activated: " + String(solarPanelsActivated));
        motor.setSpeed(solarPanelsActivated);
    }

    // Send analog input data
    if (millis() - lastSendTime >= SEND_INTERVAL) {
        sendAnalogData();
        lastSendTime = millis();
    }
}

void sendAnalogData() {
    const int ANALOG_PIN = 33;        // Analog input pin
    const int MIN_ANALOG_VALUE = 0;  // Minimum raw analog input value
    const int MAX_ANALOG_VALUE = 4095; // Maximum raw analog input value
    const int MIN_THRESHOLD = 0;     // Minimum threshold value
    const int MAX_THRESHOLD = 4000;  // Maximum threshold value

    int rawValue = analogRead(ANALOG_PIN); // Read raw analog input
    int mappedValue = map(rawValue, MIN_ANALOG_VALUE, MAX_ANALOG_VALUE, MIN_THRESHOLD, MAX_THRESHOLD); // Map to threshold values

    Serial.print("Analog input: ");
    Serial.print(rawValue);
    Serial.print(" | Mapped value: ");
    Serial.println(mappedValue);

    comControl.sendMessage(mappedValue); // Send the mapped value using comControl
}
