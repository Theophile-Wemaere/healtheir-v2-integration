
void readDHT11() 
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Serial.print("Temp : ");
  Serial.print(temperature);
  Serial.print(" | H : ");
  Serial.println(humidity);
  sendFrame(1,int(temperature*100));
  sendFrame(5,int(humidity*100));
}