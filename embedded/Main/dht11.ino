
void readDHT11() 
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  sendFrame(1,int(temperature*100));
  sendFrame(5,int(humidity*100));
}