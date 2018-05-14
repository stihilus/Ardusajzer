//Arduino Synth v0.1
//------------------
//             SLAVE
//------------------


#include <Wire.h> //inkludovanje Wire.h biblioteke

void setup()
{
  Wire.begin(5); // otvaranje/slusanje i2c komunikacije preko 5 kanala
  Wire.onReceive(receiveEvent);
  
  pinMode(13, OUTPUT); // LED kao indikator TEMPA - Pin D13
  digitalWrite(13, LOW);
}

void loop()
{
}

void receiveEvent(int howMany) //??? howMany
{
  while(Wire.available()) //Kad kod nesto stize preko i2c kanalom 5 uradi:
  {
   char c = Wire.read(); //Promenljivoj C char se dodaljuje vrednosta sa i2c
   
   if(c == 'H') // Ako je C jednako H kojeg prima sa MASTER-a onda:
   {
     digitalWrite(13, HIGH); // Pali se LED indikator
     delay(2000); //???
     tone(8, 200, 500); // Pusta se ton "tone(pin, frequency, duration)"
     
     digitalWrite(13, LOW); // Gasi se LED indikator
   }
  }
}
