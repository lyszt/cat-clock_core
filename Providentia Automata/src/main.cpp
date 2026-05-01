#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "lcd/lcd.h"
#include "clock/clock.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Clock clock(0);
// Test variables
String test = "Hello world!";

const int modeButton = 2;
int modeButtonStatus = 1;
int lastButtonRead = 1;

// Time-related functions
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
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

void handleModeButton()
{
    int currentRead = digitalRead(modeButton);

    if (currentRead != lastButtonRead)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {

        if (currentRead != modeButtonStatus)
        {
            modeButtonStatus = currentRead;

            if (modeButtonStatus == LOW)
            {
                clock.toggleMode();
                Serial.println(clock.getMode());
            }
        }
    }

    lastButtonRead = currentRead;
}

void setup()
{
    pinMode(modeButton, INPUT_PULLUP);

    clock.setPomodoroDuration(10);

    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    lcd.clear();
}

void loop()
{
    clock.cycle();
    handleModeButton();
    if (getMillis(1000) != 0) {
        lcdPrint(lcd, clock.formattedTime());
    }
}