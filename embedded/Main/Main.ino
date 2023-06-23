#include "DHT.h"
#include "MICS-VZ-89TE.h"

#define ECG PD2
#define DHTPIN PD5
#define R 11
#define G 10
#define B 9
#define DUST_D PD3
#define DUST_A A6
#define MICRO A3

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

MICS_VZ_89TE CO2SENSOR;

unsigned int rate;
float humidity;
float temperature;
int ecgLimit = 100;
int ecgCounter = 0;

int alertCounter = 0;
boolean isAlert = false;

// ECG variables
unsigned long millisECG = 0, current,duration;
int value, prev_rate = 0;
boolean wasHigh = false;

boolean alarmGoesOff = false;  
boolean buzz_state = true;

void setup() {
  Serial.begin(115200);

  pinMode(ECG,INPUT);

  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(DUST_D,OUTPUT);

  dht.begin();
  CO2SENSOR.begin();
  analogWrite(R,100);
  analogWrite(G,0);
  analogWrite(B,100);

  delay(2000);

  Serial.println("Done initializing");
}

unsigned long millis1, prev_millis = 0;
unsigned long millis2, prev_millis2 = 0;

String informations;

void loop() {
  readECG();  

  if(millis() - prev_millis2 >= 300)
  {
    prev_millis2 = millis();
    testAlert();
  }

  if(Serial.available())
  {
    while(Serial.available())
    {
      char c = (char)Serial.read();
      if(c == '\n')
      {
        handleResponse(informations);
        informations = "";
      }
      else
        informations += c;
    }
    
  }

  millis1 = millis();
  if(millis1 - prev_millis >= 3000)
  {
    if(!isAlert)
    {
      analogWrite(R,100);
      analogWrite(G,50);
      analogWrite(B,100);
    }
    prev_millis = millis1;
    readDHT11();
    readDust();
    readNoise();
    readCO2();
  }
}

void testAlert()
{
  if(isAlert)
  {
    digitalWrite(R,!digitalRead(R));
    digitalWrite(G,LOW);
    digitalWrite(B,LOW);
  }
}

void clearLeds()
{
  digitalWrite(R,LOW);
  digitalWrite(G,LOW);
  digitalWrite(B,LOW);
}