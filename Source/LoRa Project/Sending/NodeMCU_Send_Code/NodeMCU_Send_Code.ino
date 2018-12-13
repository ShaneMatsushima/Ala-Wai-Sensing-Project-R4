/**
 * Created By: Shane Matsushima
 * Date: 12/12/18
 * Purpose: This code grabs the data that is transfered from the Arduino Uno to the NodeMCU via the RX and TX pins. 
 *          The data is then processed int a float from a string and then sent to Ubidots where the data can be seen 
 *          via a graph and table up to 3 months.
 */

//Includes libraries needed
#include <HTTPSRedirect.h>
#include <UbidotsMicroESP8266.h>

//ID of the variable in Ubidots to send to 
#define ID1 "5bbd15b7c03f976a1517aae5" 

//Token of the Ubidots account the data is being sent to 
#define TOKEN "A1E-aQn8guUxXXoVL62ckFOw8y8yZkvtrk"

Ubidots client1(TOKEN);

//WiFi credentials
#define WIFISSID "palila" //change to WIFI name
#define PASSWORD "io71redbird51" //change to WIFI password

//Name of the device in Ubidots
#define NAME "Iolani MonKit 1"

//Declaring LED to be pin 13
#define LED 13

//Variable declaration
String sendvalue;
char tempval[7];

void setup() 
{
// put your setup code here, to run once:
Serial.begin(9600);

//Connects to WiFi using credentials
client1.wifiConnection(WIFISSID, PASSWORD);

//LED is an output pin since it's turning on and off
pinMode(LED, OUTPUT);
}

void loop() {

  //checks to see if the Feather sent data 
  if (Serial.available())
  {
    //Turns LED on to indicate something was received
    digitalWrite(LED, HIGH);

    //Converts what was received into an array of characters
    Serial.readBytes(tempval, 6);
    Serial.println( tempval);

    //converts the array of characters into a string and then into a float 
    String tempSend(tempval);
    float tempValSend = tempSend.toFloat();
    Serial.println( tempValSend);

    //Tunrs off LED once process is done
    digitalWrite(LED, LOW);

    //Checks t omake sure temperature data is in peramiters since the feather is not using the correct RX and TX (random data can be sent due to timing)
    if(tempValSend > 10.00 && tempValSend < 40)
    {
      //adds the temperature data into the specific Device ID and send to Ubidots
      client1.add(ID1, tempValSend);
      client1.sendAll();
    } 
  }
}
