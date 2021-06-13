#include "screen_display.hpp"

extern Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void diods_perfect()
{
    digitalWrite(TOO_LOW_LED, 0);
    digitalWrite(PERFECT_LED, 1);
    digitalWrite(TOO_HIGH_LED, 0);
}

void diods_up()
{
    digitalWrite(TOO_LOW_LED, 1);
    digitalWrite(PERFECT_LED, 0);
    digitalWrite(TOO_HIGH_LED, 0);
}

void diods_down()
{
    digitalWrite(TOO_LOW_LED, 0);
    digitalWrite(PERFECT_LED, 0);
    digitalWrite(TOO_HIGH_LED, 1);
}
void diods_clear()
{
    digitalWrite(TOO_LOW_LED, 0);
    digitalWrite(PERFECT_LED, 0);
    digitalWrite(TOO_HIGH_LED, 0);
}

bool init_display()
{
    return display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void setup_display()
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    diods_clear();
}

void display_note(Note note)
{
    //blok odpowiedzialny za wyświetlenie tonu(?)

    if (note.display2[1] == '#')
    { //jeśli jest znak # to go wyświetl obok
        //display.setFont(&FreeSerif12pt7b);
        display.fillRect(0, 0, 90, 64, BLACK);
        display.setTextSize(5);
        display.setCursor(22, 15);
        display.println(note.display2[0]); //wyświetl ton
        display.setTextSize(3);
        display.setCursor(62, 25); //wyświetl obok półton
        display.println(note.display2[1]);
        display.display();
    }
    else
    { //jeśli znaku # nie ma to wyświetl sam ton
        display.fillRect(0, 0, 90, 64, BLACK);
        display.setTextSize(5);
        display.setCursor(22, 15);
        display.println(note.display2[0]);
        display.display();
    }

    if (note.display2[2] != '-')
    {
        if (note.display2[0] > 'a' && note.display2[0] < 'z')
        {                                           //sprawdz czy ton to mala litera
            display.fillRect(50, 0, 10, 64, BLACK); //jak nie to numer oktawy w indeksie gornym
            display.setTextSize(2);
            display.setCursor(50, 15);
            display.println(note.display2[2]);
            display.display();
        }
        else
        {                                           //nwm czemu ta w indeksie dolnym miga i w ogole to jak zaczalem od if (note.display2[0] > 'A' && note.display2[0] < 'Z') czy tam 65 zamiast 'A' i 90 zamiast 'Z' to juz w ogole nie dzialalo mimo ze to samo dla malych dziala idealnie
            display.fillRect(50, 0, 10, 64, BLACK); //jak tak to numer oktawy w indeksie dolnym
            display.setTextSize(2);
            display.setCursor(50, 40); //sprawdzic
            display.println(note.display2[2]);
            display.display();
        }
    }
    else
    {
        display.fillRect(50, 0, 10, 64, BLACK);
        display.display();
    }
}

void display_tune(Note note)
{
    //blok odpowiedzialny za wyświetlanie wskazówek dotyczących dostrajania
    if (note.good == 1)
    {
        display.fillRect(100, 0, 28, 64, BLACK); //jeśli jest dobrze nastrojone to czarny protokąt przykrywa ewentualne strzałki (nie znalazłem sposobu na odświeżanie oleda częściami
        display.setTextSize(3);
        display.cp437(true); //czcionka Code Page 437 żeby dostać symbole z ASCII
        display.setCursor(100, 20);
        display.write(14); //13-♬
        display.display();
        diods_perfect();
    }
    else
    { //jeśli nie jest dobrze nastrojone to sprawdza w którą stronę stroić
        if (note.up == 1)
        {
            display.fillRect(100, 0, 28, 64, BLACK);
            display.setTextSize(3);
            display.setTextColor(WHITE);
            display.setCursor(100, 10);
            display.cp437(true);
            display.write(24); //24-↑
            display.display();
            diods_up();
        }
        else
        {
            display.fillRect(100, 0, 28, 64, BLACK);
            display.setTextSize(3);
            display.setTextColor(WHITE);
            display.setCursor(100, 36);
            display.cp437(true);
            display.write(25); //25-↓
            display.display();
            diods_down();
        }
    }
}

void displayLowBattery()
{
  //
}
