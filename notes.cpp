#include "notes.hpp"

extern struct Note currentNote = {-1, -1, "---"};

char bigNotes[12][3] =
    {
        {"C--"},
        {"C#-"},
        {"D--"},
        {"D#-"},
        {"E--"},
        {"F--"},
        {"F#-"},
        {"G--"},
        {"G#-"},
        {"A--"},
        {"A#-"},
        {"B--"},
};

char smallNotes[12][3] =
    {
        {"c--"},
        {"d#-"},
        {"d--"},
        {"d#-"},
        {"e--"},
        {"f--"},
        {"f#-"},
        {"g--"},
        {"g#-"},
        {"a--"},
        {"a#-"},
        {"b--"},
};

struct Note whichNote(double freq)
{
    struct Note o1;
    o1.up = -1;
    o1.good = -1;
    o1.display2[0] = '-';
    o1.display2[1] = '-';
    o1.display2[2] = '-';
    if (freq < C2)
        return o1;
    double note = C2;
    double prev_note = 0;
    int counter = 0;
    int o_counter = 0;
    while (freq > note)
    {
        counter++;
        prev_note = note;
        note = note * GAP;
        if (counter % 12 == 0)
        {
            o_counter++;
        }
        if (note > 15000)
        {
            return o1;
        } //b6
    }
    double good_note = 0;
    if (fabs(note - freq) < fabs(prev_note - freq))
    {
        good_note = note;
    }
    else
    {
        good_note = prev_note;
        counter--;
    }

    if (freq < good_note)
        o1.up = 1;
    else
        o1.up = 0;

    if (fabs(freq - good_note) < 0.5)
        o1.good = 1; // dostrajamy do +- 0.5 Hz
    else
        o1.good = 0;

    if (o_counter <= 2)
    {
        o1.display2[0] = bigNotes[counter % 12][0];
        o1.display2[1] = bigNotes[counter % 12][1];
    }
    else
    {
        o1.display2[0] = smallNotes[counter % 12][0];
        o1.display2[1] = smallNotes[counter % 12][1];
    }
    switch (o_counter)
    {
    case 0:
        o1.display2[2] = '2';
        break;
    case 1:
        o1.display2[2] = '1';
        break;
    case 4:
        o1.display2[2] = '1';
        break;
    case 5:
        o1.display2[2] = '2';
        break;
    case 6:
        o1.display2[2] = '3';
        break;
    case 7:
        o1.display2[2] = '4';
        break;
    case 8:
        o1.display2[2] = '5';
        break;
    case 9:
        o1.display2[2] = '6';
        break;
    default:
        o1.display2[2] = '-';
        break;
    }

    return o1;
}
