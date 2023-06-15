#define ECG PD2
#define DHT11 PD5

unsigned int rate;
int ecgLimit = 100;
int ecgCounter = 0;

boolean alarmGoesOff = false;  
boolean buzz_state = true;

void setup() {
  Serial.begin(9600);
  pinMode(ECG,INPUT);
  Serial.println("Done initializing");
}

void loop() {
  readECG();
}