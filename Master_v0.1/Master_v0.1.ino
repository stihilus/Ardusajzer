                                                    //Arduino Synth v0.1
                                                    //------------------
                                                    //            MASTER
                                                    //------------------

const int potButton = 2;                            // Potenciometer Button - Pin D2
                                                    // Ako je pritisnuto dugme potButton 
                                                    // ocitava se vrednost potenciometra
const int tempoMinus = 3;                           // tempoMinus usporava tempo - Pin D3
const int tempoPlus = 4;                            // tempoPlus ubrzava tempo - Pin D4
const int tempoReset = 5;                           // retetTempo resetuje na 500ms - Pin D3
int tempo = 250;                                    // Start Tempo u ms
int brojac = 1;

#include <Wire.h>                                   //ukljucivanje biblioteke Wire.h

void setup()
{
  pinMode(A3, INPUT);
  pinMode(potButton, INPUT);
  pinMode(tempoPlus, INPUT);
  pinMode(tempoMinus, INPUT);
  pinMode(tempoReset, INPUT);
  Serial.begin(9600);
  Wire.begin();                                     // Otvaranje i2c komunikacije A4(SDA),A5(SCL)
}

void loop()
{
  Wire.beginTransmission(5);                        // pocetak i2c komunikacija preko 5 kanala
  
  if(brojac == 1)
  {
    Wire.write('1');                                // slanje karaktera slave arduinu
  }
  else if(brojac == 2)
  {
    Wire.write('1');
    Wire.write('2');
  }
  else if(brojac == 3)
  {
    Wire.write('1');
    Wire.write('3');
  }
  else if(brojac == 4)
  {
    Wire.write('1');
    Wire.write('4');
  }

  if(brojac<=3)
  {
    brojac = brojac + 1;
  }
  else
  {
    brojac = 1;
  }
    
  Wire.endTransmission();                           // kraj komunikacije

                                                    // Provera da li je potButton HIGH ako jeste 
                                                    // ocitava vrednost potenciometra povezanog na A3
  if(digitalRead(potButton) == HIGH)
  {
    tempo = map(analogRead(A3),0,1023,250,750);
  } 

  // TEMPO MINUS
  else if(digitalRead(tempoMinus) == HIGH)
  {
    tempo = tempo - 50;
  } 

  // TEMPO PLUS
    else if(digitalRead(tempoPlus) == HIGH)
  {
    tempo = tempo + 50;
  } 

  // TEMPO RESET
    else if(digitalRead(tempoReset) == HIGH)
  {
    tempo = 500;
  } 
  
  delay(tempo);                                     // DELAY u zavistnosti od tempa
  Serial.println(tempo);
}
