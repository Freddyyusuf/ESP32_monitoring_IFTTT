
const char* resource  = "/trigger/ESP32_data/with/key/MAMPIZheSz3pA43Gndx7t";
const char* resource2 = "/trigger/Alarm_Trigger/with/key/MAMPIZheSz3pA43Gndx7t";

const char* trigger_server = "maker.ifttt.com";

void makeIFTTTRequest(long Sievert) {
  Serial.print("Connecting to "); 
  Serial.print(trigger_server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(trigger_server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);

  // Temperature in Celsius
  String jsonObject = String("{\"value1\":\"") + Sievert + "\"}";
                      
                      
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + trigger_server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}

//---------------------------------------------------
//---------------------------------------------------

void IFTTTRequest_Al(long Sievert) {
  Serial.print("Connecting to "); 
  Serial.print(trigger_server);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(trigger_server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resource);

  // Temperature in Celsius
  String jsonObject = String("{\"value1\":\"") + Sievert + "\"}";
                      
                      
  client.println(String("POST ") + resource2 + " HTTP/1.1");
  client.println(String("Host: ") + trigger_server); 
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; // 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
}
