#include <ESP8266WiFi.h>

#include <HTTPSRedirect.h>

#include <UbidotsMicroESP8266.h>

#define ID1 "5ac7ef7dc03f972ba56665c8" // temp sensor
#define TOKEN "A1E-4gfwu1P5Vt4Gi6L3m7y5ziXpoRPD52" // Put here your Ubidots TOKEN

Ubidots client1(TOKEN);

//WiFi credentials
#define WIFISSID "Insert WiFi SSID"
#define PASSWORD "Insert WiFi Password"

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
