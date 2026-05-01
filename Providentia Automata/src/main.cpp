#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "lcd/lcd.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastMillis = 0;

unsigned long getMillis(unsigned long time)
{
    unsigned long currentMillis = millis();

    if (currentMillis - lastMillis >= time)
    {
        lastMillis = currentMillis;
        return lastMillis;
    }

    return 0;
}

void setup()
{
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
}

void loop()
{

    if (getMillis(5000) != 0)
    {
        if (Serial.available())
        {
            lcd.clear();
            lcdPrint(lcd);
        }
    }
}