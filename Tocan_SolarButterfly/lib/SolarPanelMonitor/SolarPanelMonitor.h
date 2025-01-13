#ifndef SOLAR_PANEL_MONITOR_H
#define SOLAR_PANEL_MONITOR_H

#include <Arduino.h>

#define SOLAR_PANELS 2 // Number of solar panels
#define THRESHOLD 2500 // ADC threshold value
#define SAMPLE_SIZE 100 // Number of samples for the LPF

// Predefined pins for solar panels
const int panelPins[SOLAR_PANELS] = {33, 32};//, 34, 35, 36};

class SolarPanelMonitor {
private:
    float filteredValues[SOLAR_PANELS];
    int sampleIndex[SOLAR_PANELS];
    int samples[SOLAR_PANELS][SAMPLE_SIZE];
    int solarThreshold;
public:
    void begin();
    int checkPanels();
    void setThreshold(int threshold);
};

#endif