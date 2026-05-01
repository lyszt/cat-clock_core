#include "lcd.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void lcdPrint(LiquidCrystal_I2C &lcd, String text)
{
    lcd.clear();
    lcd.setCursor(0, 0);

    for(int i = 0; i < text.length(); i++) {
        char incomingByte = text[i];
        if(incomingByte == 10) {
            break;
        }
        lcd.print(incomingByte);
    }
}

