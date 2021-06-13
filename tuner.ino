#include "screen_display.hpp"
#include "fourier.hpp"

#define SQUARE_OUT 2 //PE4 / OC3B
#define MODE_SW 3 //PE5
#define MODE_INFO_LED 41 //PD4
#define VOLTAGE_PIN A0 //PF0
#define LOW_BATT_LEVEL 716 //~3.5V is too low

double peak=0;
bool aToneMode = false;
bool isVoltageLow = false;
void checkModeSwitch();
bool checkBatteryLevel();
void setup() 
{
    Serial.begin(115200); 
    pinMode(MODE_SW,INPUT);
    pinMode(SQUARE_OUT,OUTPUT);
    pinMode(VOLTAGE_PIN,INPUT);


    //440Hz squarewave
    //TIMER3 registers
    
    TCCR3A = 0b00000000; //CTC mode, 256 prescaler, toggle OC3B pin (disabled at the beginning)
    TCCR3B = 0b00001100;
    OCR3AL = 70;         //toggle every 256*(70+1) pulse => 440,14Hz
    
    if(!init_display()) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  setup_display();
  Serial.println("OK");
}
 
void loop() 
{  
  checkModeSwitch();
  if(checkBatteryLevel())
  {
    displayLowBattery();
  }
  if(!aToneMode)
  {
    //disable squarewave (COM3A0 = 0)
    TCCR3A = 0b00000000;
    //low on SQUARE OUT
    PORTE &= ~(1<<4);
    
    fill_fft_arrays();
    peak = find_freq();
    peak=peak*0.98; // strojenie stroika xd
    Serial.println(peak);    
    Serial.println(analogRead(A8)); 
    currentNote=whichNote(peak);
    display_note(currentNote);
    display_tune(currentNote);
  }
  else
  {
    //enable squarewave (COM3A0 = 1)
    TCCR3A = 0b00010000; //CTC mode, 256 prescaler, toggle OC3B pin
  }


}

void checkModeSwitch()
{
  if(digitalRead(MODE_SW))
  {
    aToneMode = true;
    digitalWrite(MODE_INFO_LED, LOW);
  }
  else 
  {
    aToneMode = false;
    digitalWrite(MODE_INFO_LED, HIGH);
  }
}

bool checkBatteryLevel()
{
  int readVoltage = analogRead(VOLTAGE_PIN);
  if(readVoltage <= LOW_BATT_LEVEL)
  {
    isVoltageLow = true;
    return true;
  }
  else
  {
    isVoltageLow = false;
    return false;
  }
}
