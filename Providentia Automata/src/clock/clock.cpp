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
    LiquidCrystal_I2C *lcd = &this->lcd;

    switch (this->mode)
    {
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
        if (this->turned_on == true)
        {
            this->turned_on = false;
            lcd->noDisplay();
            lcd->noBacklight();
        }
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

    // the divinity of the sacred meow
    meow();

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

// what a cutely named function
void Clock::meow()
{
    // Adding slight variation each call
    int rand_pitch = random(-40, 41);
    int rand_range = random(-20, 21);

    int base_freq = 900 + rand_pitch; 
    int range = 200 + rand_range;

    //Me
    // We use a larger step (0.2) to move through the first 90 degrees quickly
    for (float i = 0; i < PI / 2; i += 0.2) 
    {
        int freq = base_freq + (sin(i) * range);
        tone(this->buzzerPin, freq);
        delay(5); 
    }

    // "Oww"
    // We use a much smaller step (0.05) and a slightly longer delay
    // to stretch the descent from the peak back to base_freq
    for (float i = PI / 2; i < PI; i += 0.05) 
    {
        int freq = base_freq + (sin(i) * range);
        tone(this->buzzerPin, freq);
        
        int final_delay = 25 + rand_delay;
        delay(final_delay < 5 ? 5 : final_delay); 
    }

    noTone(this->buzzerPin);
    // the mathematics of the perfect meow
}