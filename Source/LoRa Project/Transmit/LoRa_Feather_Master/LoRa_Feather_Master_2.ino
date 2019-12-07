/**
 * Created By: Shane Matsushima
 * Date: 12/12/18
 * Purpose: Transmit temperature data collected by the Dallas Temperature sensor and send it over via RF using hte LoRa RFM
 *          which will then be uploaded to Ubidots. The purpose for the project is to collect temperature data from entering streams
 *          and the Ala Wai to get a better understanding of how sceintists can restore the polluted stream.
 **/

//Libraries included 
#include <SPI.h>
#include <RH_RF95.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Defining pins that the LoRa breakout baord uses
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

//Defining the pin the temperature sensor hooks up to
#define ONE_WIRE_BUS 12

//Defining LED pin for checking if the system sent a packet
#define LED 13

//variable temp used as a place holder for the temperature data collected
double temp;
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

//Calling the oneWire library for the temperature sensor 
OneWire oneWire (ONE_WIRE_BUS);

//Dallas has its own library to create the sensor and output the data in celcius 
DallasTemperature sensor(&oneWire);

//Declaration for device ID as well as packet size being sent 
char radiopacket[7];
char deviceID = 'A';
 
void setup() 
{
  //connects LED pin to an output (LED is an output)
  pinMode(LED, OUTPUT); 
  pinMode(RFM95_RST, OUTPUT);
  
  digitalWrite(RFM95_RST, HIGH);
 
  Serial.begin(9600);
  delay(100);
 
  Serial.println("Arduino LoRa TX Test!");
 
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
 
  while (!rf95.init()) 
  {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) 
  {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}

// packet counter, we increment per xmission
int16_t packetnum = 0;  
 
void loop()
{
  Serial.println("Sending to rf95_server");

  //grabs temperature data from sensor
  temp = getTemp();
  Serial.println(temp);


  //Places the character array from the tempnumChar into the radiopacket array with a Device ID
  radiopacket = package(deviceID, temp)
 
  Serial.println("Sending..."); delay(10);

  //sends the [acket of data while indicating it sent using the LED
  if(rf95.send(radiopacket, 6))
  {
    digitalWrite(LED, HIGH);
  }
  
  digitalWrite(LED, LOW);
  Serial.println("Waiting for packet to complete..."); delay(10);
  rf95.waitPacketSent();
  
  delay(1000);

} // void loop

//function to grab the temperature data as a float 
float getTemp()
{
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  if(temp > -127 && temp <50){
  return temp;
  }
}

/**
 * Function to label the packet being sent with the appropriate device ID
 * 
 * How It Works: 
 * It places the specified Device ID character in the front of the data and changes the data into a string for the Feather to send over via RF
 * 
 */

String package(char ID, float data)
{
  String finalData;
  char tempNumChar[7];
  String tempNumStr = String(data);
  tempNumStr.toCharArray(tempNumChar, 6);

  finalData[0] = ID;

  for(int i = 1; i <= 5; i++)
  {
    finalData[i] = tempNumChar[i - 1];
  }

  finalData[6] = 0;

  return finalData;
}