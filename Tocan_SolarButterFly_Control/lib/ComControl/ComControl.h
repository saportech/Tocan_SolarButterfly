#ifndef COMCONTROL_H
#define COMCONTROL_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

class ComControl {
public:
    void begin();
    int checkInput();
    void sendMessage(int threshold);

private:
    static void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len);
    uint8_t peerAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    static int solarNum;
    static unsigned long lastReceiveTime;
};

#endif
