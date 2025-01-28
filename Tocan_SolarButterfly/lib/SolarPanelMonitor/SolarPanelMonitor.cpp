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

void SolarPanelMonitor::checkPanels(float filteredVals[], bool statuses[], int &panelsExceeded) {
    panelsExceeded = 0;
    for (int i = 0; i < SOLAR_PANELS; i++) {
        int rawValue = analogRead(panelPins[i]);
        samples[i][sampleIndex[i]] = rawValue;
        sampleIndex[i] = (sampleIndex[i] + 1) % SAMPLE_SIZE;

        float sum = 0;
        for (int j = 0; j < SAMPLE_SIZE; j++) {
            sum += samples[i][j];
        }
        filteredValues[i] = sum / SAMPLE_SIZE;
        statuses[i] = (filteredValues[i] > solarThreshold);
        if (statuses[i]) {
            panelsExceeded++;
        }
        filteredVals[i] = filteredValues[i];
    }
}

void SolarPanelMonitor::setThreshold(int threshold) {
    solarThreshold = threshold;
}
