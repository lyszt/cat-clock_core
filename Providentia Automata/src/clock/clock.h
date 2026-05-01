#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class Clock { 
    public: 
    // in milliseconds
        unsigned long current_time;
        unsigned long start_time;
        unsigned long pomodoro_duration;
        int mode; // 0: disabled, 1: alarm mode, 2: pomodoro mode
        int pomodoro_cycle;
        int num_modes = 3; 

        Clock(int insert_mode) {
            mode = insert_mode;
        }

        void setMode(int mode);
        int getMode();
        void toggleMode();
        void setTime(unsigned long milliseconds);
        unsigned long getTime();
        String formattedTime();
        void setPomodoroDuration(int minutes);
        unsigned long getTimeElapsed();
        void cycle();
        
        
};

#endif