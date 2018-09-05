#include <Wire.h>
#include <LCD5110_Graph.h>

LCD5110 myGLCD(8,9,10,12,11);
extern unsigned char SmallFont[];

const int pot = 2;
const int ledPin = 13;
const int tempoMinus = 3;
const int tempoPlus = 4;
const int tempoReset = 5;
int tempo = 140;
int brojac = 1;
int trajanjeLed = 100;
int stanjeLed = false;
unsigned long trenutak = 0;

void setup()
{
  Wire.begin();
  
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  
  Serial.begin(9600);
  
  pinMode(A3,INPUT);
  pinMode(pot,INPUT_PULLUP);
  pinMode(tempoMinus,INPUT_PULLUP);
  pinMode(tempoPlus,INPUT_PULLUP);
  pinMode(tempoReset,INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
}

void loop()
{
  
  Wire.beginTransmission(5);
  if(brojac == 1)
  {
    Wire.write('1');
    Serial.println("Poslato 1.");
    treptanje();
  }
  else if(brojac == 2)
  {
    Wire.write('1');
    Wire.write('2');
    Serial.println("Poslato 1 i 2.");
    treptanje();
  }
  else if(brojac == 3)
  {
    Wire.write('1');
    Wire.write('3');
    Serial.println("Poslato 1 i 3.");
    treptanje();
  }
  else if(brojac == 4)
  {
    Wire.write('1');
    Wire.write('4');
    Serial.println("Poslato 1 i 4.");
    treptanje();
  }
  
  Wire.endTransmission();
  
  if(brojac <= 3)
  {
    brojac = brojac + 1;
  }
  else
  {
    brojac = 1;
  }
  
  Serial.print("Brojac je: "); Serial.println(brojac);
  
  myGLCD.clrScr();
  myGLCD.print("ARDUSAJZER", 12, 15);
  myGLCD.print("RULES!", 25, 30);
  myGLCD.update();
  
  if(digitalRead(pot) == LOW)
  {
    tempo = map(analogRead(A3),0,1023,80,240);
    myGLCD.clrScr();
    myGLCD.print(String(tempo), 32, 20);
    myGLCD.update();
  }
  else if(digitalRead(tempoMinus) == LOW)
  {
    if(tempo>=85)
    {
      tempo = tempo - 5;
      myGLCD.clrScr();
      myGLCD.print(String(tempo), 32, 20);
      myGLCD.update();
    }
    else
    {
      tempo = 80;
      myGLCD.clrScr();
      myGLCD.print("min BPM", 22, 20);
      myGLCD.update();
      Serial.println("min BPM");
    }
  }
  else if(digitalRead(tempoPlus) == LOW)
  {
    if(tempo<=235)
    {
      tempo = tempo + 5;
      myGLCD.clrScr();
      myGLCD.print(String(tempo), 32, 20);
      myGLCD.update();
    }
    else
    {
      tempo = 240;
      myGLCD.clrScr();
      myGLCD.print("max BPM", 22, 20);
      myGLCD.update();
      Serial.println("max BPM");
    }
  } 
  else if(digitalRead(tempoReset) == LOW)
  {
    tempo = 140;
    myGLCD.clrScr();
    myGLCD.print(String(tempo), 32, 20);
    myGLCD.update();
  } 
  
  delay(60000/tempo);
  Serial.print(tempo); Serial.println(" BMP");
}

void treptanje()
{
  unsigned long trenutno = millis();
  
  if((trenutno - trenutak)>=trajanjeLed)
  {
    trenutak = trenutno;
    if(stanjeLed==LOW)
  {
    stanjeLed = HIGH;
  }
  else
  {
    stanjeLed=LOW;
  }
  digitalWrite(ledPin,stanjeLed);
  }
}
