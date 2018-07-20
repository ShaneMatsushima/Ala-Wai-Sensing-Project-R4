#include <ESP8266WiFi.h>

#include <HTTPSRedirect.h>

#include <UbidotsMicroESP8266.h>

#define ID1 "Temperature Sensor ID" 
#define TOKEN "Put Ubidots TOKEN here"

Ubidots client1(TOKEN);

//WiFi credentials
#define WIFISSID "Palila"
#define PASSWORD "io71redbird51"

#define NAME "Hello World!"

// The ID below comes from Google Sheets.
const char *GScriptId = "AKfycbycAHYDLwX3tB6NYYjtANRg1Lhs-sEg7xZb941NFLWVIwsxWzwt";

// Push data on this interval
const int dataPostDelay = 300000; 
const char* host = "script.google.com";
const char* googleRedirHost = "script.googleusercontent.com";

const int httpsPort =  443;
HTTPSRedirect client(httpsPort);
String url = String("/macros/s/") + GScriptId + "/exec?";

const char* fingerprint = "F0 5C 74 77 3F 6B 25 D7 3B 66 4D 43 2F 7E BC 5B E9 28 86 AD";
 
String sendvalue;
float tempval;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
client1.wifiConnection(WIFISSID, PASSWORD);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
  sendvalue = Serial.readString();
  tempval = sendvalue.toFloat();
  Serial.println(tempval);
  client1.add(ID1, tempval);
  client1.sendAll();
  postData(tempval);
  }
}

void postData( float temps){
  if (!client.connected()){
    Serial.println("Connecting to client again..."); 
    client.connect(host, httpsPort);
  }
  
  String urlFinal = url + "&temps=" + String(temps) + "&name=" + String(NAME);
  client.printRedir(urlFinal, host, googleRedirHost);
  
}
