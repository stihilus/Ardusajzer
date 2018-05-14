//Arduino Synth v0.1
//------------------
//            MASTER
//------------------

Test GitHub

const int potButton = 2; 
// Potenciometer Button - Pin D2
// Ako je pritisnuto dugme potButton propusta se vrednost potenciometra
const int tempoMinus = 3; // tempoMinus usporava tempo - Pin D3
const int tempoPlus = 4; // tempoPlus ubrzava tempo - Pin D4
const int resetTempo = 5; // retetTempo resetuje na 500ms - Pin D3
int tempo = 100; // Start Tempo in ms


#include <Wire.h> //inkludovanje Wire.h biblioteke

void setup()
{
  pinMode(A3, INPUT);
  pinMode(potButton, INPUT);
  digitalWrite(potButton, LOW);
  pinMode(tempoPlus, INPUT);
  pinMode(tempoMinus, INPUT);
  pinMode(resetTempo, INPUT);
  
  Serial.begin(9600);
  Wire.begin(); // Otvaranje i2c komunikacije A4(SDA),A5(SCL)
}

void loop()
{
  digitalWrite(potButton, LOW); // za svaki slucaj 

  Wire.beginTransmission(5); // pocetak i2c komunikacija preko 5 kanala
  Wire.write('H'); // Slanje H karaktera SLAVE arduinu
  Wire.endTransmission(); // Zatravanje komunikacije

  // Provera da li je potButton HIGH ako jeste propusta vrednost A3 potenciometra
  if(digitalRead(potButton) == HIGH)
  {
    potOcitavanje();
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
    else if(digitalRead(resetTempo) == HIGH)
  {
    tempo = 500;
  } 

  
  delay(tempo); // DELAY u zavistnosti od tempa
  Serial.println(tempo);
}


// FUNKCIJA za ocitavanje POTENCIOMETRA na A3
int potOcitavanje()
{
  tempo = analogRead(A3);
  delay(tempo); //???
  return tempo;
}
