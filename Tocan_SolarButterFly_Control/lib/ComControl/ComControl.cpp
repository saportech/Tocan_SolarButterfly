#include "ComControl.h"

int ComControl::receivedValue = -1; // Initialize with a default value

void ComControl::begin() {
    WiFi.mode(WIFI_STA); // Set ESP32 as Station

    // Print device MAC address
    uint8_t mac[6];
    WiFi.macAddress(mac);
    Serial.print("Device MAC Address: ");
    for (int i = 0; i < 6; i++) {
        Serial.printf("%02X", mac[i]);
        if (i < 5) Serial.print(":");
    }
    Serial.println();

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the callback for receiving messages
    esp_now_register_recv_cb(onReceive);
}

void ComControl::onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {
    if (len == sizeof(int)) { // Ensure the length matches an integer
        memcpy(&receivedValue, data, sizeof(int)); // Copy the raw bytes into receivedValue
        Serial.print("Received integer: ");
        Serial.println(receivedValue);
    } else {
        Serial.println("Invalid message length received.");
    }
}

int ComControl::checkInput() {
    if (receivedValue > 0) { // Check if a valid value is received
        int value = receivedValue;
        receivedValue = -1; // Reset after returning the value
        return value;
    }
    return -1; // No valid input
}

void ComControl::sendMessage(int panelsActivated) {
    uint8_t message[sizeof(panelsActivated)]; // Create a byte buffer for the integer
    memcpy(message, &panelsActivated, sizeof(panelsActivated)); // Copy the integer into the buffer

    esp_err_t result = esp_now_send(peerAddress, message, sizeof(panelsActivated)); // Send the buffer

    if (result == ESP_OK) {
        Serial.println("Message sent successfully");
    } else {
        Serial.println("Error sending the message");
    }
}
