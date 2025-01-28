#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

class OLED {
public:
    OLED();
    bool begin(uint8_t address = 0x3C);
    void write(const String &line1);
    void clear();

private:
    Adafruit_SSD1306 display;
};

#endif // OLED_H
