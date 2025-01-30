#ifndef SOLAR_PANEL_MONITOR_H
#define SOLAR_PANEL_MONITOR_H

#include <Arduino.h>

#define SOLAR_PANELS 5
#define SAMPLE_SIZE 100

const int panelPins[SOLAR_PANELS] = {32, 35, 34, 39, 36};

class SolarPanelMonitor {
private:
    float filteredValues[SOLAR_PANELS];
    int sampleIndex[SOLAR_PANELS];
    int samples[SOLAR_PANELS][SAMPLE_SIZE];
    int solarThreshold;
    bool panelStatuses[SOLAR_PANELS];
public:
    void begin();
    void checkPanels(float filteredVals[], bool statuses[], int &panelsExceeded);
    void setThreshold(int threshold);
};

#endif
