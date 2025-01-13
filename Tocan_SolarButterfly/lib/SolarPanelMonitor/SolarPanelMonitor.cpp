// SolarPanelMonitor.cpp
#include "SolarPanelMonitor.h"

void SolarPanelMonitor::begin() {
    analogReadResolution(12);
    for (int i = 0; i < SOLAR_PANELS; i++) {
        pinMode(panelPins[i], INPUT);
        filteredValues[i] = 0;
        sampleIndex[i] = 0;
        for (int j = 0; j < SAMPLE_SIZE; j++) {
            samples[i][j] = 0;
        }
    }
}

int SolarPanelMonitor::checkPanels() {
    static unsigned long lastPrintTime = 0;
    const unsigned long printInterval = 1000; // 1 second
    int panelsExceeded = 0; // Reset at the start of each function call
    
    for (int i = 0; i < SOLAR_PANELS; i++) {
        int rawValue = analogRead(panelPins[i]);
        samples[i][sampleIndex[i]] = rawValue;
        sampleIndex[i] = (sampleIndex[i] + 1) % SAMPLE_SIZE;

        // Calculate the average for the LPF
        float sum = 0;
        for (int j = 0; j < SAMPLE_SIZE; j++) {
            sum += samples[i][j];
        }
        filteredValues[i] = sum / SAMPLE_SIZE;

        if (filteredValues[i] > solarThreshold) {
            panelsExceeded++; // Increment for each panel above the threshold
            unsigned long currentTime = millis();
            if (currentTime - lastPrintTime >= printInterval) {
                Serial.print("Panel ");
                Serial.print(i + 1);
                Serial.println(" OK");
                lastPrintTime = currentTime;
            }
        }
    }
    return panelsExceeded;
}

void SolarPanelMonitor::setThreshold(int threshold) {
    solarThreshold = threshold;
}