#include <Arduino.h>
#include "SolarPanelMonitor.h"
#include "Com.h"
#include "OLED.h"

SolarPanelMonitor monitor;
Device device;
OLED oled;

unsigned long lastSentTime = 0;
const unsigned long interval = 100;
int solarThreshold = 2500;

// Global variables for panel data
float filteredVals[SOLAR_PANELS];
bool statuses[SOLAR_PANELS];
int panelsActivated;

void updateThreshold();
void updateOLEDDisplay();

void setup() {
  Serial.begin(115200);
  Serial.println("Solar Panel Monitor");

  monitor.begin();
  device.begin();
  oled.begin();
}

void loop() {
  updateThreshold();

  monitor.checkPanels(filteredVals, statuses, panelsActivated);

  if (millis() - lastSentTime >= interval) { 
    updateOLEDDisplay();
    Serial.println("Panels Activated: " + String(panelsActivated));
    device.sendMessage(panelsActivated);
    lastSentTime = millis();
  }
  
}

void updateThreshold() {
  solarThreshold = device.getThreshold();
  monitor.setThreshold(solarThreshold);
}

void updateOLEDDisplay() {
  String oledMessage = "Panels:\n";
  for (int i = 0; i < SOLAR_PANELS; i++) {
    oledMessage += "P" + String(i + 1) + ": " + String(filteredVals[i], 2) + " " + (statuses[i] ? "ON" : "OFF") + "\n";
  }
  oledMessage += "Total: " + String(panelsActivated) + "\n";
  oledMessage += "Threshold: " + String(solarThreshold);
  oled.write(oledMessage);
}
