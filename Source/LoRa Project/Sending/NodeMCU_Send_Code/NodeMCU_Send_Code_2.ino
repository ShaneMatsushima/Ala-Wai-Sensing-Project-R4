/**
 * Created By: Shane Matsushima
 * Date: 12/5/18
 * Purpose: This code grabs the data that is transfered from the Arduino Uno to the NodeMCU via the RX and TX pins. 
 *          The data is then processed int a float from a string and then sent to Ubidots where the data can be seen 
 *          via a graph and table up to 3 months. This code also supports up to two receivers sending to one Ubidots device.
 * Device ID Example:
 *          Device ID: A
 *          Value Send: 20.00
 *          Received Value Rx: A20.00
 */

 //Includes libraries needed
#include <HTTPSRedirect.h>
#include <UbidotsMicroESP8266.h>

//ID of the variable in Ubidots to send to 
#define ID1 "Place Variable ID Here" 
#define ID2 "Place Variable ID Here" 

//Device ID for incoming data
#define DD1 A
#define DD2 B

//Token of the Ubidots account the data is being sent to 
#define TOKEN "Place Token Here"

Ubidots client1(TOKEN);

//WiFi credentials
#define WIFISSID "Change" //change to WIFI name
#define PASSWORD "Change" //change to WIFI password

//Name of the device in Ubidots
#define NAME "Place Name of Ubidots Device Here"

//Declaring LED to be pin 13
//This LED signifies if a signal was received via serial
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
    Serial.readBytes(tempval, 7);
    Serial.println( tempval);

    //converts the array of characters into a string and then into a float
    // The data is sorted to a specific ID based on the device indicator at the front  of the data
    if(tempval[0] == DD1)
    {
        Serial.println(getData(tempVal));
        client1.add(ID1, getData(tempVal));
        client1.sendAll();
    }
    if(tempval[0] == DD2)
    {
        Serial.println(getData(tempVal));
        client1.add(ID2, getData(tempVal));
        client1.sendAll();
    }
    else
    {
        Serial.println("Error: Device Uknown");
    }

  } // Serial available

} // void loop 


/**
 * Function takes the raw data from the RF and retreives only the data value without the device ID
 * 
 */
float getData(String raw)
{
  String tempRaw(raw);
  string tempSend = tempRaw.substring(1,6);
  float tempValSend = tempSend.toFloat();
  return tempValSend;
}

