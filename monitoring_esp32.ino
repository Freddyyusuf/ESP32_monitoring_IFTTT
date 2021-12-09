#include<WiFi.h>
#include <WebServer.h>

//--------------------------------
#include "index.h" 
#include "trigger_webhooks.h"
//--------------------------------
#define LOGtime 1000                      
#define Minute 60000                     

TaskHandle_t Task2;                      //Create Task2 object


// SSID dan pass Router
const char* ssid = "Enanjalica";
const char* password = "akumabahehe";

//---------------------------------
////////////////////////////////////////
// variabel global counter
int Counts = 0;                          
unsigned long previousMillis = 0;         
int AVGCPM = 0;                           
int TenSecCPM = 0;
float Sievert = 0;
float cpm_send= 0;
int rloop=0;

int COUNTS[10];                         
int t = 0;

int cc= 5;
////////////////////////////////////
//----------------------------------

WebServer server(80);                 //Starting Webserver at port 80;

//----------------------------------

void handleRoot() {
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}

void handleInput() {
 long a = cpm_send;       
 String inputValue = String(a);
 server.send(200, "text/plane", inputValue); 

}


//----------------------------------

void IRAM_ATTR isr()
  {
  Counts++;
  }


//----------------------------------


void Task2code(void*pvParameters){          //Task to be pinned to core 0
  //rloop=0;
  for(;;){
    //int pinTime= millis();
    cpm_send= AVGCPM;
    server.handleClient();
    
    if(rloop==1){
      makeIFTTTRequest(cpm_send); 
      delay(10);
      
      rloop=0;
    }
      
   }
}


//-----------------------------------------------------------------------
// SETUP FUNCTION
//-----------------------------------------------------------------------


void setup(void){
  //--------------------------------------------
   for (int x = 0; x < 10 ; x++) {          
        COUNTS[x] = 0;                          
        }
  
    attachInterrupt(27, isr, FALLING);     
  
  //-------------------------------------------
  
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to WiFi router
  Serial.println("");

 // pinMode(LED,OUTPUT); 
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
 
  server.on("/", handleRoot);      
  server.on("/readInput", handleInput); 

  server.begin();                 
  Serial.println("HTTP server started");


   //vv Pin task2code routine to core 0 vv//
    xTaskCreate(                              
                      Task2code,   //Task function. //
                      "Task2",     //name of task. //
                      10000,       //Stack size of task //
                      NULL,        //parameter of the task //
                      1,           //priority of the task //
                      &Task2      //Task handle to keep track of created task //
                      );          //pin task to core 0 //                  
    delay(500); 
}

//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------

void loop(void){
     
      unsigned long currentMillis = millis();
          if(currentMillis - previousMillis > LOGtime){
              previousMillis = currentMillis;

              COUNTS[t] = Counts;
              for (int y = 0; y < 10 ; y++) {               
                TenSecCPM = TenSecCPM + COUNTS[y];            
              }
              AVGCPM = 6* TenSecCPM; 
              TenSecCPM = 0;
              t++ ;
              if (t > 9) { 
                t = 0 ;
                Serial.println(AVGCPM);
                rloop++;
              }

              Counts = 0;

          }

}
////--------------------------------------
