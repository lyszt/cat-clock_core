#include "clock.h"
#include "../sounds/sounds.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

enum modes
{
    DISABLED,
    CHRONOMETRE,
    POMODORO
};


// Clock functions

unsigned long Clock::getTimeElapsed()
{
    this->current_time = millis() - this->start_time;
    return this->current_time;
}

void Clock::setMode(int mode)
{
    this->mode = mode;
}

int Clock::getMode()
{
    return this->mode;
}

void Clock::setTime(unsigned long milliseconds)
{
    this->current_time = milliseconds;
}

unsigned long Clock::getTime()
{
    return this->current_time;
}

void Clock::setPomodoroDuration(int minutes)
{
    this->pomodoro_duration = minutes * 60000UL;
}

void Clock::toggleMode()
{
    this->mode = (this->mode + 1) % this->num_modes;
    LiquidCrystal_I2C *lcd = &this->lcd;

    switch (this->mode)
    {
    case CHRONOMETRE:
        this->start_time = millis();
        this->current_time = 0;
        soundPowerOn(this->buzzerPin);
        break;

    case POMODORO:
        this->start_time = millis();
        this->current_time = 0;
        this->pomodoro_cycle = 0;
        soundModeSwitch(this->buzzerPin);
        break;

    default:
        this->current_time = 0;
        if (this->turned_on == true)
        {
            this->turned_on = false;
            lcd->noDisplay();
            lcd->noBacklight();
        }
        soundOff(this->buzzerPin);
        break;
    }

    if (!turned_on && this->mode != DISABLED)
    {
        LiquidCrystal_I2C *lcd = &this->lcd;

        lcd->display();
        lcd->backlight();
        lcd->clear();
        this->turned_on = true;
    }

}

void Clock::cycle()
{
    switch (this->mode)
    {
    case DISABLED:
        break;

    case CHRONOMETRE:
        this->getTimeElapsed();
        break;

    case POMODORO:
    {
        this->getTimeElapsed();

        if (this->pomodoro_cycle == 0)
        {
            if (this->current_time >= 1500000UL) // 25 * 60 * 1000 - 25 minutos,
            // sadly I was forced to do this
            // unreadable shit
            {
                this->start_time = millis();
                this->current_time = 0;
                this->pomodoro_cycle = (this->pomodoro_cycle + 1) % 2;
                // the divinity of the sacred meow
                meow(this->buzzerPin);
            }
            break;
        }
        else if (this->pomodoro_cycle == 1)
        {
            if (this->current_time >= this->pomodoro_duration)
            {
                this->start_time = millis();
                this->current_time = 0;
                this->pomodoro_cycle = (this->pomodoro_cycle + 1) % 2;
                // the divinity of the sacred meow
                meow(this->buzzerPin);
            }
            break;
        }
        break;
    }

    default:
        break;
    }

    tickMeow(this->buzzerPin);
    tickMelody(this->buzzerPin);
}
String Clock::formattedTime()
{
    unsigned long current_time = this->current_time;
    int seconds = (int)(current_time / 1000) % 60;
    int minutes = (int)(current_time / 1000 / 60) % 60;
    int hours = (int)(current_time / 1000 / 60 / 60) % 24;

    char buffer[10];
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);

    return String(buffer);
}

