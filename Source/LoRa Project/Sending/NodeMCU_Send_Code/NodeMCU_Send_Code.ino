

#include <HTTPSRedirect.h>

#include <UbidotsMicroESP8266.h>

#define ID1 "5bbd15c3c03f9769f430c81c" 
#define TOKEN "A1E-aQn8guUxXXoVL62ckFOw8y8yZkvtrk"

Ubidots client1(TOKEN);

//WiFi credentials
#define WIFISSID "gkklan"
#define PASSWORD "noahjacobkayla"

#define NAME "Iolani MonKit 1"

#define LED 13

String sendvalue;
char tempval[7];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
client1.wifiConnection(WIFISSID, PASSWORD);
pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("*");
  if (Serial.available()){
    digitalWrite(LED, HIGH);
     Serial.readBytes(tempval, 6);
Serial.println( tempval);
String tempSend(tempval);
float tempValSend = tempSend.toFloat();
Serial.println( tempValSend);
digitalWrite(LED, LOW);
  
  if(tempValSend > 10.00){
  client1.add(ID1, tempValSend);
  client1.sendAll();
    } 
  }
}
