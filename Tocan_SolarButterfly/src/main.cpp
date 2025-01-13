#include <Arduino.h>
#include "SolarPanelMonitor.h"
#include "Com.h"

SolarPanelMonitor monitor;
Device device;

unsigned long lastSentTime = 0;
const unsigned long interval = 1000; // 1 second
int solarThreshold = 2500;

void updateThreshold();

void setup() {
  Serial.begin(115200);
  Serial.println("Solar Panel Monitor");

  monitor.begin();
  device.begin();
}

void loop() {

  updateThreshold();

  int panelsActivated = monitor.checkPanels();

  if (panelsActivated > 0 && (millis() - lastSentTime >= interval)) {
    Serial.println(String(panelsActivated) + " Solar panels activated " + String(millis()));
    device.sendMessage(panelsActivated);
    lastSentTime = millis();
  }
}

void updateThreshold() {

  solarThreshold = device.getThreshold();
  monitor.setThreshold(solarThreshold);

}
