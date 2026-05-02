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

    tickMeow();
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
    tickMeow(true);
}

void Clock::tickMeow(bool reset)
{
    static bool active = false;
    static float i = 0.0;
    static int phase = 0;
    static unsigned long last_time = 0;
    static int base_freq = 900;
    static int range = 200;
    static int step_delay = 25;

    if (reset)
    {
        int rand_pitch = random(-40, 41);
        int rand_range = random(-20, 21);
        int rand_delay = random(-5, 6);

        active = true;
        i = 0.0;
        phase = 0;
        last_time = millis();
        base_freq = 900 + rand_pitch;
        range = 200 + rand_range;
        step_delay = 25 + rand_delay < 5 ? 5 : 25 + rand_delay;
        return;
    }

    if (!active) return;

    //Me — step 0.2, 5ms per step
    //Oww — step 0.05, longer delay to stretch the descent
    unsigned long interval = (phase == 0) ? 5 : step_delay;
    if (millis() - last_time < interval) return;
    last_time = millis();

    int freq = base_freq + (sin(i) * range);
    tone(this->buzzerPin, freq);

    if (phase == 0)
    {
        i += 0.2;
        if (i >= PI / 2) { phase = 1; i = PI / 2; }
    }
    else
    {
        i += 0.05;
        if (i >= PI) { noTone(this->buzzerPin); active = false; }
    }
    // the mathematics of the perfect meow
}