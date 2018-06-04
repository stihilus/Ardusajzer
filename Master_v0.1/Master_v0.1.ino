#include <Wire.h> // Biblioteka za i2c komunikaciju
#include <LCD5110_Graph.h> // Biblioteka za LCD

LCD5110 myGLCD(8,9,10,12,11); 

// LCD PIN------Arduino PIN
// 1 RST        D12
// 2 CE         D11
// 3 DC         D10
// 4 DIN        D9
// 5 CLK        D8
// 6 VCC        5V - 3.3V
// 7 LIGHT      GND
// 8 GND        GND

extern unsigned char SmallFont[]; // Odabir fonta

const int pot = 2; // Dugme koje propusta vrednost potenciometra
const int ledPin = 13; // signalni LED / Tempo LED
const int tempoMinus = 3; // Usporavanje tempa
const int tempoPlus = 4; // Ubrzavanje tempa
const int tempoReset = 5; // Resetovanje tempa
int tempo = 140;
int brojac = 1;
int trajanjeLed = 100;
int stanjeLed = false;
unsigned long trenutak = 0;

void setup()
{
  Wire.begin(); // Otvanje i2c veze 
  
  myGLCD.InitLCD(); // Aktiviranje LCD
  myGLCD.setFont(SmallFont); // Setovanje fonta
  
  Serial.begin(9600);
  
  pinMode(A3,INPUT);
  pinMode(pot,INPUT_PULLUP);
  pinMode(tempoMinus,INPUT_PULLUP);
  pinMode(tempoPlus,INPUT_PULLUP);
  pinMode(tempoReset,INPUT_PULLUP);
  pinMode(ledPin,OUTPUT);
}

void loop() // Slanje 1 2 3 4 "char"-a sa mastera
{
  
  Wire.beginTransmission(5); // Salje samo 1
  if(brojac == 1)
  {
    Wire.write('1');
    Serial.println("Poslato 1.");
    treptanje();
  }
  else if(brojac == 2) // Salje i 1 i 2
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
  
  Wire.endTransmission(); // Prekid i2c komunikacije
  
  if(brojac <= 3) // Brojac 
  {
    brojac = brojac + 1;
  }
  else
  {
    brojac = 1;
  }
  
  Serial.print("Brojac je: "); Serial.println(brojac);

  // Stampanje ardusajzer logo-a na LCD-u
  myGLCD.clrScr();
  myGLCD.print("ARDUSAJZER", 12, 15);
  myGLCD.print("RULES!", 25, 30);
  myGLCD.update();
  
  if(digitalRead(pot) == LOW) // Ako je pot dugme pritisnuto propustaje vrednost i setuj tempo
  {
    tempo = map(analogRead(A3),0,1023,80,240);
    myGLCD.clrScr();
    myGLCD.print(String(tempo), 32, 20);
    myGLCD.update();
  }
  else if(digitalRead(tempoMinus) == LOW) // ako je minus dugme pritisnuto skida tempo
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
  
  delay(60000/tempo); // TEMPO
  Serial.print(tempo); Serial.println(" BMP");
}

void treptanje() // Indikator tempa LED
{
  if((millis() - trenutak)>=trajanjeLed)
  {
    trenutak = millis();
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
