#include "DHT.h"

#define ECG PD2
#define DHTPIN PD5
#define R 11
#define G 10
#define B 9

#define DUST_D PD3
#define DUST_A A6

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


unsigned int rate;
float humidity;
float temperature;
int ecgLimit = 100;
int ecgCounter = 0;

boolean alarmGoesOff = false;  
boolean buzz_state = true;

void setup() {
  Serial.begin(9600);

  pinMode(ECG,INPUT);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(DUST_D,OUTPUT);

  dht.begin();
  Serial.println("Done initializing");
}

unsigned long millis1, prev_millis = 0;

void loop() {
  readECG();
  millis1 = millis();

  if(millis1 - prev_millis >= 1000)
  {
    prev_millis = millis1;
    readDHT11();
    readDust();
  }
}