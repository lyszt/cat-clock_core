#include "clock.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


void Clock::setMode(int mode) {
    this->mode = mode;
}

int Clock::getMode(){
    return this->mode;
}

void Clock::setTime(int milliseconds) {
    this->current_time = milliseconds;
}

int Clock::getTime() {
    return this->current_time;
}

void Clock::setPomodoroDuration(int milliseconds){
    this->pomodoro_duration = milliseconds;
}

