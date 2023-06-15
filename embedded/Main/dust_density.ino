int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void readDust()
{
  digitalWrite(DUST_D,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(DUST_A); 

  delayMicroseconds(deltaTime);
  digitalWrite(DUST_D,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured * (3.3 / 1024.0);

  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = 170 * calcVoltage - 0.1;
  sendFrame(3,int(dustDensity*100));
}