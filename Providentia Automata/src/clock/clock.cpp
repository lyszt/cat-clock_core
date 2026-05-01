#include "clock.h"
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

    switch (this->mode)
    {
    case DISABLED:
        this->current_time = 0;
        break;

    case CHRONOMETRE:
        this->start_time = millis();
        this->current_time = 0;
        break;
        
    case POMODORO:
        this->start_time = millis();
        this->current_time = 0;
        this->pomodoro_cycle = 0;
        break;

    default:
        this->current_time = 0;
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
        
        int minutes = (int)(this->current_time / 1000 / 60) % 60;
        if (this->pomodoro_cycle == 0)
        {
            if (minutes >= 25)
            {
                this->start_time = millis();
                this->current_time = 0;
                this->pomodoro_cycle = (this->pomodoro_cycle + 1) % 2;
            }
            break;
        }
        else if (this->pomodoro_cycle == 1)
        {
            if (minutes >= (this->pomodoro_duration / 60000UL))
            {
                this->start_time = millis();
                this->current_time = 0;
                this->pomodoro_cycle = (this->pomodoro_cycle + 1) % 2;
            }
            break;
        }
        break;
    }

    default:
        break;
    }
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
