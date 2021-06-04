
#ifndef notes_hpp
#define notes_hpp

#include <Arduino.h>
#include "math.h"

#define GAP 1.059463
#define C2 16.351598

extern char bigNotes[12][3];
extern char smallNotes[12][3];

struct Note
{
    int up;           // jesli up jest na 1 to trzeba dostrajac w gore, jesli 0 to w dol
    int good;         // jesli na 1 to nastrojone
    char display2[3]; // znaki do wyswieenia, '-' oznacza nic
};

extern struct Note currentNote;

struct Note whichNote(double freq);

#endif
