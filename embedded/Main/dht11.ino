
void readDHT11() 
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print(temperature);
  Serial.print(" ");
  Serial.println(humidity);
  sendFrame(1,int(temperature*100));
  sendFrame(5,int(humidity*100));
}