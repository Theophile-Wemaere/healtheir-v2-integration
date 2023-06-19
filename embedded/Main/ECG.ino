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
    if(rate < 300)
    {
      Serial.print("Rate : ");
      Serial.println(rate);
      if((rate > prev_rate + 50 || rate < prev_rate - 50) && prev_rate != 0 )
      {
        prev_rate = 0;
        wasHigh = false;
      }
      else 
      {
        prev_rate = rate;
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
    }
  }

  if(value == 0 && wasHigh)
  {
    wasHigh = false;
  }
}
