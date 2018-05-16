                                                    //Arduino Synth v0.1
                                                    //------------------
                                                    //            MELODY
                                                    //------------------


#include <Wire.h>                                   // inkludovanje Wire.h biblioteke
const int ledPin = 13;
int ledLife = 100;
int tonePin = 8;
int toneFrequency = 200;
int toneDuration = 500;

void setup()
{
  Wire.begin(5);                                    // otvaranje/slusanje i2c komunikacije preko 5 kanala
  Wire.onReceive(receiveEvent);
  pinMode(ledPin, OUTPUT);                              // LED kao indikator TEMPA - Pin D13
  digitalWrite(ledPin, LOW);
}

void loop()
{
}

void receiveEvent(int howMany)                      //??? howMany
{
  while(Wire.available())                           //Kad kod nesto stize preko i2c kanalom 5 uradi:
  {
   char c = Wire.read();                            //Promenljivoj C char se dodaljuje vrednosta sa i2c
   
   if(c == 'A')                                  // Ako je C jednako stringu kojeg prima sa MASTER-a onda:
   {
     digitalWrite(ledPin, HIGH);                    // Pali se LED indikator
     delay(ledLife);                                // Trajanje sveljenja diode
     tone(tonePin, toneFrequency, toneDuration);    // Pusta se ton "tone(pin, frequency, duration)"
     digitalWrite(ledPin, LOW);                     // Gasi se LED indikator
   }
  }
}
