#include <Wire.h>

const int tempoPin = 0;
const int brojPinova = 8;
const int brojTonova = 8;
const int tonePin = 11;
const int freqPins[brojPinova] = {2,3,5,12,7,8,9,10};
const int ledPin = 13;
int toneFrequency[brojTonova] = {450,500,550,600,650,700,750,800};
int toneDuration[brojTonova] = {200,200,200,200,200,200,200,200};
int brojacTempo = 1;
int brojacTone = 0;
int stanjeDugme[brojTonova] = {false,false,false,false,false,false,false,false};
int opcija2 = 1000;
unsigned long trenutak = 0;
int duziStisak[brojTonova] = {false,false,false,false,false,false,false,false};
int sviraNotu[brojTonova] = {true,true,true,true,true,true,true,true};

void setup()
{
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  pinMode(A3,INPUT);
  pinMode(A2, INPUT);
  pinMode(tempoPin,INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  for(int i = 0; i<brojPinova; i++)
  {
    pinMode(freqPins[i],INPUT_PULLUP);
  }
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(tempoPin)==LOW)
  {
    if(brojacTempo<=3)
    {
      brojacTempo = brojacTempo + 1;
      //Serial.print("Brojac je: "); Serial.println(brojacTempo);
    }
    else
    {
      brojacTempo = 1;
      //Serial.print("Brojac je: "); Serial.println(brojacTempo);
    }
  }
  else
  {
    for(int j = 0; j<brojPinova; j++)
    {
      if(digitalRead(freqPins[j])==LOW)
      {
        if(stanjeDugme[j] == false)
        {
          stanjeDugme[j] = true;
          trenutak = millis();
        }
        if((millis()-trenutak>opcija2)&&(duziStisak[j] == false))
        {
          duziStisak[j] = true;
          toneFrequency[j] = map(analogRead(A2),0,1023,15,7900);
          toneDuration[j] = map(analogRead(A3),0,1023,46,4000);
          Serial.print("Frekvencija za "); Serial.print(j+1); Serial.print(". zvuk je: "); Serial.println(toneFrequency[j]);
          Serial.print("Trajanje za "); Serial.print(j+1); Serial.print(". zvuk je: "); Serial.println(toneDuration[j]);
        }
      }
      else
      {
        if(stanjeDugme[j] == true)
        {
          if(duziStisak[j] == true)
          {
            duziStisak[j] = false;
          }
          else
          {
            sviraNotu[j] = !sviraNotu[j];
            //Serial.print(j+1); Serial.println("Status note promenjen.");
          }
          stanjeDugme[j] = false;
        }
      }
    }
  }
  delay(100);
//  for(int i = 0;i<brojTonova;i++)
//  {
//    Serial.println(toneFrequency[i]);
//  }
}

void receiveEvent(int howMany)
{
  while(Wire.available())
  {
    
    //Serial.println(brojacTempo);
        
    char c = Wire.read();
    int d = c - '0';
    
    //Serial.println("Primljen karakter "); Serial.println(c);
    
    if(d==brojacTempo)
    {
      if(brojacTone<8)
      {
        brojacTone = brojacTone + 1;
      }
      else
      {
        brojacTone = 1;
      }
      if(sviraNotu[brojacTone-1]==true)
      {
        tone(tonePin, toneFrequency[brojacTone-1], toneDuration[brojacTone-1]);
        //Serial.println("svira");
        //Serial.println(brojacTone);
        //Serial.println(toneFrequency[brojacTone-1]);
        Serial.println(brojacTone);
      }
    }
    else
    {
      digitalWrite(ledPin,LOW);
    }
  }
}
