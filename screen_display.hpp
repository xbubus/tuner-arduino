#ifndef screen_display_hpp
#define screen_display_hpp

#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif12pt7b.h>
#include "notes.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define PERFECT_LED 38 //PD7
#define TOO_HIGH_LED 39 //PD6
#define TOO_LOW_LED 40//PD5
//#define MODE_INFO_LED 41//PD4

extern Adafruit_SSD1306 display;

void diods_perfect();
void diods_up();
void diods_down();
void diods_clear();

bool init_display();
void setup_display();
void display_note(Note note);
void display_tune(Note note);


#endif
