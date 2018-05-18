                                                    //Arduino Synth v0.1
                                                    //------------------
                                                    //            MELODY
                                                    //------------------


#include <Wire.h>                                   // inkludovanje Wire.h biblioteke
const int tempoPin = 0;
const int ledPin = 13;
const int freqPins[8] = {1,2,3,4,5,6,7,8};
int tonePin = 9;
int toneFrequency[8] = {200,0,0,0,0,0,0,0};
int toneDuration[8] = {500,0,0,0,0,0,0,0};
int ledLife = 100;
int brojac = 1;

void setup()
{
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  for(int i = 0; i < 8; i++)
  {
    pinMode(freqPins[i],INPUT);
  }
  Wire.begin(5);                                    // otvaranje/slusanje i2c komunikacije preko 5 kanala
  Wire.onReceive(receiveEvent);
  pinMode(ledPin, OUTPUT);                          // LED kao indikator TEMPA - Pin D13
}

void loop()
{
  if(digitalRead(tempoPin)==HIGH)
  {
    if(brojac<=3)
    {
      brojac = brojac + 1;
    }
    else
    {
      brojac = 1;
    }
  }

  for(int i = 0; i < 8; i++)
  {
    if(digitalRead(i),HIGH)
    {
      toneFrequency[i] = map(analogRead(A1),0,1023,15,7900);
      toneDuration[i] = map(analogRead(A1),0,1023,46,4000);
      Serial.print("Frekvencija za "); Serial.print(i); Serial.print(". zvuk je: "); Serial.println(toneFrequency[i]);
      Serial.print("Trajanje za "); Serial.print(i); Serial.print(". zvuk je: "); Serial.println(toneDuration[i]);
    }
  }
}


void receiveEvent(int howMany)                      //??? howMany
{
  while(Wire.available())                           //Kad kod nesto stize preko i2c kanalom 5 uradi:
  {
    char c = Wire.read();                            //Promenljivoj C char se dodaljuje vrednosta sa i2c
    int d = c - '0';
   
    if(d == brojac)
    {
      for(int i = 0; i < 8; i++)
      {
        tone(tonePin, toneFrequency[i], toneDuration[i]);    // Pusta se ton "tone(pin, frequency, duration)"
        Serial.print("Svira zvuk "); Serial.println(i);
        digitalWrite(ledPin, HIGH);                    // Pali se LED indikator
        delay(ledLife);                                // Trajanje sveljenja diode
        digitalWrite(ledPin, LOW);                     // Gasi se LED indikator
      }
    }
  }
}
