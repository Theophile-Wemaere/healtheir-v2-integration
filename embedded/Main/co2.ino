// https://github.com/HGrabas/MICS-VZ-89TE

int prev_co2 = 0;
int prev_voc = 0;

void readCO2() { // run over and over

  CO2SENSOR.readSensor();

  float co2 = CO2SENSOR.getCO2();
  float voc = CO2SENSOR.getVOC();

  if((co2 <= prev_co2 + 100 || voc <= prev_voc + 100) || (prev_co2 == 0 && prev_voc ==0))
  {
    prev_voc = voc; prev_co2 = co2;
    sendFrame(4,co2*100);
    sendFrame(6,voc*100);
  }
}