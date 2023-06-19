// https://github.com/HGrabas/MICS-VZ-89TE

void readCO2() { // run over and over

  CO2SENSOR.readSensor();

  float co2 = CO2SENSOR.getCO2();
  float voc = CO2SENSOR.getVOC();

  sendFrame(4,co2*100);
  sendFrame(6,voc*100);
}