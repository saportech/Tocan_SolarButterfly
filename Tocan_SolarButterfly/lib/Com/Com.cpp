// Com.cpp
#include "Com.h"

int Device::threshold = 0;

Device::Device() {}

void Device::begin() {
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    esp_now_register_send_cb(onSend);
    esp_now_register_recv_cb(onReceive);
}


void Device::sendMessage(int panelsActivated) {
    uint8_t message[sizeof(panelsActivated)]; // Create a byte buffer for the integer
    memcpy(message, &panelsActivated, sizeof(panelsActivated)); // Copy the integer into the buffer

    esp_err_t result = esp_now_send(peerAddress, message, sizeof(panelsActivated)); // Send the buffer

    if (result == ESP_OK) {
        Serial.println("Message sent successfully");
    } else {
        Serial.println("Error sending the message");
    }
}

void Device::onSend(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Send status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void Device::onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {
    if (len != sizeof(int)) {
        Serial.println("Invalid message size received");
        return;
    }

    int receivedValue;
    memcpy(&receivedValue, data, sizeof(receivedValue));

    Serial.print("Received value: ");
    Serial.println(receivedValue);

    // Update the threshold variable with the received value
    threshold = receivedValue;

    Serial.print("Updated threshold to: ");
    Serial.println(threshold);
}

int Device::getThreshold() {
    return threshold;
}