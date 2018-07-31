#include <UbidotsMicroESP8266.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#define ID1 "5ac7ef7dc03f972ba56665c8" // temp sensor
#define TOKEN "A1E-089b50f2fbcff4a2ceb723dd5d44b070805e" // Put here your Ubidots TOKEN
#define WIFISSID "Palila"
#define PASSWORD "io71redbird51"
#define ONE_WIRE_BUS D1


OneWire oneWire (ONE_WIRE_BUS);

DallasTemperature sensor(&oneWire);

Ubidots client1(TOKEN);

//float values for the code
float value;


//integer values for the code

/*
// The ID below comes from Google Sheets.
// Towards the bottom of this page, it will explain how this can be obtained
const char *GScriptId = "place google sheets script ID here";
// Push data on this interval
const int dataPostDelay = 300000; 
const char* host = "script.google.com";
const char* googleRedirHost = "script.googleusercontent.com";
const int httpsPort =  443;
HTTPSRedirect client(httpsPort);
String url = String("/macros/s/") + GScriptId + "/exec?";
const char* fingerprint = "F0 5C 74 77 3F 6B 25 D7 3B 66 4D 43 2F 7E BC 5B E9 28 86 AD";
*/

void setup() {
  // Put your setup code here, to run once:
  // Begin the Serial Monitor
  Serial.begin(115200);

  
  client1.wifiConnection(WIFISSID, PASSWORD);

}



void loop() {
value = 27;
  client1.add(ID1, value); 
  client1.sendAll(true);
  delay(300000);

}

float getTemp(){
    sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  if(temp > -127 && temp <50){
    return temp;
  }
}

