unsigned long millisECG = 0, current,duration;
int value;
boolean wasHigh = false;

void readECG()
{
  value = digitalRead(ECG);
  if(value == 1 && !wasHigh)
  {
    wasHigh = true;
    current = millis();
    duration = current - millisECG;
    millisECG = current;
    rate = 60000/duration;
    Serial.println(rate);
    sendFrame(0,rate);
    if(rate > ecgLimit)
    {
      ecgCounter += 1;
      if(ecgCounter >= 5)
      {
        alarmGoesOff = true;
      }
    }
    else
    {
      ecgCounter = 0;
      alarmGoesOff = false;
    }
  }

  if(value == 0 && wasHigh)
  {
    wasHigh = false;
  }
}
