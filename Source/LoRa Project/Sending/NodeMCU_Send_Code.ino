

#include <HTTPSRedirect.h>

#include <UbidotsMicroESP8266.h>

#define ID1 "5bbd1581c03f976992ecf059" 
#define TOKEN "A1E-aQn8guUxXXoVL62ckFOw8y8yZkvtrk"

Ubidots client1(TOKEN);

//WiFi credentials
#define WIFISSID "Palila"
#define PASSWORD "io71redbird51"

#define NAME "Iolani MonKit 1"


String sendvalue;
char tempval[7];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
//while(!Serial){;}
client1.wifiConnection(WIFISSID, PASSWORD);

}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("*");
  if (Serial.available()){
     Serial.readBytes(tempval, 6);
Serial.println( tempval);
String tempSend(tempval);
float tempValSend = tempSend.toFloat();
Serial.println( tempValSend);
     
    //Serial.write(tempval);
  if(tempValSend > 10.00){
  client1.add(ID1, tempValSend);
  client1.sendAll();
    } 
  }
}
