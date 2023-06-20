// Frame creation values :
byte start = 0xFE;

byte send_data = 0x30;

byte sensors[] = {
  0x01, // ECG
  0x02, // Temperature
  0x03, // noise
  0x04, // Dust
  0x05, // CO2
  0x06, // Humidity
  0x07  // VOC
};

/*
                Start of trame     Command       sensors        payload size    payload    checksum
byte frame[] = {     start      , send_data ,  sensors[type] , sizeof(value), (byte)value, checksum}; 

*/

void sendFrame(int type, long value)
{
  char hexValue[5];
  sprintf(hexValue, "%X",value); 

  uint16_t size = String(hexValue).length();

  byte frame[4 + size]; 

  frame[0] = start;
  frame[1] = send_data;
  frame[2] = sensors[type];
  frame[3] = size;

  for (int i = 0; i < size; i++) {
    char hexChar = hexValue[i];
    if (hexChar >= '0' && hexChar <= '9') {
      frame[4 + i] = hexChar - '0';
    } else if (hexChar >= 'A' && hexChar <= 'F') {
      frame[4 + i] = hexChar - 'A' + 10;
    } else if (hexChar >= 'a' && hexChar <= 'f') {
      frame[4 + i] = hexChar - 'a' + 10;
    }
  }

  size_t length = sizeof(frame)/sizeof(frame[0]);
  
  byte checksum = calculateChecksum(frame, length);
  frame[length] = checksum;
  
  for(int i =0; i<length+1;i++) {
    Serial.print(frame[i],HEX);
  }
  Serial.print('\n');

}

byte calculateChecksum(const byte* data, size_t length) 
{
  byte checksum = 0;
  
  for (size_t i = 0; i < length; i++) {
    checksum ^= data[i];
  }
  return checksum;
}

void handleResponse(String informations)
{
    Serial.print("Value : ");
    Serial.println(informations);
    
    if(informations == "read_ok")
    {
      digitalWrite(R,0);
      digitalWrite(G,100);
      digitalWrite(B,0);
    }
    else if(informations =="read_bad")
    {
      digitalWrite(R,100);
      digitalWrite(G,0);
      digitalWrite(B,0);
    }
    else if(informations.startsWith("command:"))
    {
      digitalWrite(R,0);
      digitalWrite(G,0);
      digitalWrite(B,100);
    }

}