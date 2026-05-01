#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Clock { 
    public: 
    // in milliseconds
        int current_time;
        int pomodoro_duration;
        int mode; // 1: alarm mode, 2: pomodoro mode

        void setMode(int mode);
        int getMode();
        void setTime(int milliseconds);
        int getTime();
        void setPomodoroDuration(int milliseconds);
        
};

#endif