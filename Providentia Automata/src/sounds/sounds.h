#ifndef SOUNDS_H
#define SOUNDS_H

#include <Arduino.h>
#include "notes.h"

void soundPowerOn(int pin);
void soundModeSwitch(int pin);
void soundOff(int pin);
void playMelody(int pin, const int* melody, int noteCount, int tempo);
void tickMelody(int pin);

// what a cutely named function
void meow(int pin);
void tickMeow(int pin, bool reset = false);

#endif
