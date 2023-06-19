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

// ECG variables
unsigned long millisECG = 0, current,duration;
int value, prev_rate = 0;
boolean wasHigh = false;

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
  CO2SENSOR.begin();

  Serial.println("Done initializing");
}

unsigned long millis1, prev_millis = 0;
unsigned long millis2, prev_millis2 = 0;

void loop() {
  readECG();
  
  millis1 = millis();
  if(millis1 - prev_millis >= 600000)
  {
    prev_millis = millis1;
    readDHT11();
    readDust();
  }

  millis2 = millis();
  if(millis2 - prev_millis2 >= 10000) 
  {
    prev_millis2 = millis2;
    readNoise();
    readCO2();
  }
}