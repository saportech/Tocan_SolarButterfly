#include "ComControl.h"

int ComControl::solarNum = 0;
unsigned long ComControl::lastReceiveTime = 0;

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

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add broadcast peer");
        return;
    }

    esp_now_register_recv_cb(onReceive);
}

void ComControl::onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {
    if (len == sizeof(int)) { // Ensure the length matches an integer
        int receivedValue;
        memcpy(&receivedValue, data, sizeof(receivedValue)); // Copy the raw bytes into receivedValue
        //Serial.print("Received integer: ");
        //Serial.println(receivedValue);
        solarNum = receivedValue;
        lastReceiveTime = millis();
    } else {
        Serial.println("Invalid message length received.");
    }
}

int ComControl::checkInput() {
    if (millis() - lastReceiveTime >= 3000) {
        Serial.println("No message received for 3 seconds, Butterfly board is disconnected");
        solarNum = 0;
        return solarNum;
    }
    else if (solarNum > -1) {
        int value = solarNum;
        return value;
    }
    return -1; // No valid input
}

void ComControl::sendMessage(int threshold) {
    uint8_t message[sizeof(threshold)]; // Create a byte buffer for the integer
    memcpy(message, &threshold, sizeof(threshold)); // Copy the integer into the buffer

    esp_err_t result = esp_now_send(peerAddress, message, sizeof(threshold)); // Send the buffer

    if (result == ESP_OK) {
        //Serial.println("Message sent successfully");
    } else {
        Serial.println("Error sending the message");
    }
}
