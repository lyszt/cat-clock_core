#include "lcd.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void lcdPrint(LiquidCrystal_I2C &lcd)
{
    lcd.setCursor(0, 0);
    while (Serial.available() > 0)
    {
        char incomingByte = Serial.read();
        // skip the line-feed character
        if (incomingByte == 10)
        {
            break;
        }
        // display each character to the LCD
        lcd.print(incomingByte);
    }
}

