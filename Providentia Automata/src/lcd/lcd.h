#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void lcdPrint(LiquidCrystal_I2C &lcd, String text);


#endif