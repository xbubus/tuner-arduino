#include "screen_display.hpp"
#include "fuhrer.hpp"

double peak=0;
void setup() 
{
    Serial.begin(115200); 
     
    if(!init_display()) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  setup_display();
  Serial.println("OK");
}
 
void loop() 
{  
    

    fill_fft_arrays();
    peak = find_freq();
    peak=peak*0.98; // strojenie stroika xd
    Serial.println(peak);    
    Serial.println(analogRead(A8)); 
    currentNote=whichNote(peak);
    display_note(currentNote);
    display_tune(currentNote);

}
