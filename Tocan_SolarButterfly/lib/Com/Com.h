// Com.h
#ifndef COM_H
#define COM_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define CONTROL_MAC_ADDRESS {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC} // MAC address of the control ESP32

class Device {
private:
    uint8_t peerAddress[6] = CONTROL_MAC_ADDRESS; // MAC address of the control
    static void onSend(const uint8_t *mac_addr, esp_now_send_status_t status);
    static void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len);
    static int threshold;
public:
    Device();
    void begin();
    void sendMessage(int panelsActivated);
    int getThreshold();
};

#endif