#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
const int serPin = 11;
const int rclkPin = 12;
const int srclkPin = 13;
const int tempoPin = 0;
const int brojPinova = 8;
const int brojTonova = 8;
const int tonePin = 10;
const int freqPins[brojPinova] = {2,3,4,5,6,7,8,9};
String toneNames[] = {"B0","C1","CS1","D1","DS1","E1","F1","FS1","G1","GS1","A1","AS1","B1","C2","CS2","D2","DS2","E2","F2","FS2","G2","GS2","A2","AS2","B2","C3","CS3","D3","DS3","E3","F3","FS3","G3","GS3","A3","AS3","B3","C4","CS4","D4","DS4","E4","F4","FS4","G4","GS4","A4","AS4","B4","C5","CS5","D5","DS5","E5","F5","FS5","G5","GS5","A5","AS5","B5","C6","CS6","D6","DS6","E6","F6","FS6","G6","GS6","A6","AS6","B6","C7","CS7","D7","DS7","E7","F7","FS7","G7","GS7","A7","AS7","B7","C8","CS8","D8","DS8"};
int tonePitches[] = {31,33,35,37,39,41,44,46,49,52,55,58,62,65,69,73,78,82,87,93,98,104,110,117,123,131,139,147,156,165,175,185,196,208,220,233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988,1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976,2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951,4186,4435,4699,4978};
int toneFrequency[brojTonova] = {450,500,550,600,650,700,750,800};
int toneDuration[brojTonova] = {200,200,200,200,200,200,200,200};
int brojacTempo = 1;
int brojacTone = 0;
int stanjeDugme[brojTonova] = {false,false,false,false,false,false,false,false};
int opcija2 = 1000;
unsigned long trenutak = 0;
int duziStisak[brojTonova] = {false,false,false,false,false,false,false,false};
int sviraNotu[brojTonova] = {true,true,true,true,true,true,true,true};
byte svira = 255;

void setup()
{
  Wire.begin(5);
  Wire.onReceive(receiveEvent);
  pinMode(A3,INPUT);
  pinMode(A2, INPUT);
  pinMode(tempoPin,INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("ARDUSAJZER RULES");
  
  for(int i = 0; i<brojPinova; i++)
  {
    pinMode(freqPins[i],INPUT_PULLUP);
  }
  Serial.begin(9600);

  pinMode(serPin,OUTPUT);
  pinMode(rclkPin,OUTPUT);
  pinMode(srclkPin,OUTPUT);

  writeRegisters();
}

void writeRegisters()
{
  digitalWrite(rclkPin,LOW);
  shiftOut(serPin, srclkPin, LSBFIRST, svira);
  digitalWrite(rclkPin,HIGH);
}

void loop()
{
  //lcd.clear();
  //lcd.setCursor(0, 0);
  //lcd.print("ARDUSAJZER RULES");
  
  if(digitalRead(tempoPin)==LOW)
  {
    if(brojacTempo<=3)
    {
      brojacTempo = brojacTempo + 1;
    }
    else
    {
      brojacTempo = 1;
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
          sviraNotu[j] = !sviraNotu[j];
          bitWrite(svira, j, sviraNotu[j]);
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
            toneFrequency[j] = tonePitches[map(analogRead(A2),0,1023,0,89)];
            toneDuration[j] = map(analogRead(A3),0,1023,100,1000);
            Serial.println(map(analogRead(A2),0,1023,0,89));
            Serial.println(tonePitches[map(analogRead(A2),0,1023,0,89)]);
            Serial.println(toneNames[map(analogRead(A2),0,1023,0,89)]);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print(toneNames[map(analogRead(A2),0,1023,0,89)]);
          }
          stanjeDugme[j] = false;
        }
      }
    }
  }

  writeRegisters();
  
  delay(10);
}

void receiveEvent(int howMany)
{
  while(Wire.available())
  {        
    char c = Wire.read();
    int d = c - '0';
    
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
      }
    }
  }
}
