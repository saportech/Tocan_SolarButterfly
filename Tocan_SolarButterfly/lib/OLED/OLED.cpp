#include "OLED.h"

OLED::OLED()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

bool OLED::begin(uint8_t address) {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("OLED initialization failed");
        return false;
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.display();
    return true;
}

void OLED::write(const String &line1) {
    display.clearDisplay();

    // Set the cursor for the first line
    display.setCursor(0, 0); 
    display.print(line1);

    display.display();
}

void OLED::clear() {
    display.clearDisplay();
    display.display();
}
