const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
unsigned long startMillis;  
unsigned int peakToPeak = 0; // peak-to-peak level
unsigned int signalMax;
unsigned int signalMin;

 
void readNoise()
{
  signalMax = 0;                            //minimum value
  signalMin = 1024;  
  startMillis= millis(); 
  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(MICRO);         //get reading from microphone
    if (sample < 1024)                  // toss out spurious readings
    {
        if (sample > signalMax)
        {
          signalMax = sample;           // save just the max levels
        }
        else if (sample < signalMin)
        {
          signalMin = sample;           // save just the min levels
        }
    }
  }

  peakToPeak = signalMax - signalMin;   // max - min = peak-peak amplitude
  int db = map(peakToPeak,20,800,30,100);  //calibrate for deciBels
  //Serial.println(db);
  sendFrame(2,db);
}