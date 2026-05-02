#include "sounds.h"

// non-blocking melody player
// encodes melody as {NOTE, DURATION, NOTE, DURATION, ...}
// duration: 4=quarter, 8=eighth, negative=dotted (x1.5)
static struct {
    bool          active;
    const int*    melody;
    int           totalNotes;
    int           wholenote;
    int           currentNote;
    unsigned long noteStart;
    int           noteDuration;
    bool          inPause;
} mp = {false};

static void startNote(int pin)
{
    int divider = mp.melody[mp.currentNote + 1];
    mp.noteDuration = divider > 0
        ? mp.wholenote / divider
        : (int)((mp.wholenote / abs(divider)) * 1.5f);

    int note = mp.melody[mp.currentNote];
    if (note == REST) noTone(pin);
    else              tone(pin, note);

    mp.noteStart = millis();
    mp.inPause   = false;
}

void playMelody(int pin, const int* melody, int noteCount, int tempo)
{
    mp.active      = true;
    mp.melody      = melody;
    mp.totalNotes  = noteCount;
    mp.wholenote   = (60000 * 4) / tempo;
    mp.currentNote = 0;
    startNote(pin);
}

void tickMelody(int pin)
{
    if (!mp.active) return;

    unsigned long elapsed = millis() - mp.noteStart;

    if (!mp.inPause)
    {
        if (elapsed >= (unsigned long)(mp.noteDuration * 0.9f))
        {
            noTone(pin);
            mp.inPause = true;
        }
        return;
    }

    if (elapsed < (unsigned long)mp.noteDuration) return;

    mp.currentNote += 2;
    if (mp.currentNote >= mp.totalNotes * 2) { mp.active = false; return; }
    startNote(pin);
}

static const int powerOnMelody[] = {
    NOTE_A3, 16,
    NOTE_A3, 16,
    NOTE_C5, 16,
    NOTE_A3, 16,
    REST,    16,
    NOTE_G3, 16,
    NOTE_C5, 16,
    NOTE_G3, 16,
};
static const int powerOffMelody[] = {
    NOTE_D3, 16,
    NOTE_E3, 16,
    NOTE_E3, 16,
    NOTE_D3, 16,
    NOTE_C3, 16,
    NOTE_C3, 16,
};
static const int modeSwitchMelody[]  = { NOTE_E3, 16, NOTE_B3, 8 };

void soundPowerOn(int pin)    { playMelody(pin, powerOnMelody,    8, 100); }
void soundOff(int pin)        { playMelody(pin, powerOffMelody,   6, 100); }
void soundModeSwitch(int pin) { playMelody(pin, modeSwitchMelody, 2, 120); }

// what a cutely named function
void meow(int pin)
{
    tickMeow(pin, true);
}

void tickMeow(int pin, bool reset)
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

    int freq = base_freq + (int)(sin(i) * range);
    tone(pin, freq);

    if (phase == 0)
    {
        i += 0.2;
        if (i >= PI / 2) { phase = 1; i = PI / 2; }
    }
    else
    {
        i += 0.05;
        if (i >= PI) { noTone(pin); active = false; }
    }
    // the mathematics of the perfect meow
}
