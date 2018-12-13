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

  //grabs temperature daata from sensor
  temp = getTemp();
  Serial.println(temp);

  //converts the data collected into a string
  String tempNumStr =  String(temp);
  Serial.println(tempNumStr);

  //puts the temperature string into an array of characters
  char tempNumChar[6];
  tempNumStr.toCharArray(tempNumChar, 6);
  Serial.println(tempNumChar);

  //Places the character array from the tempnumChar into the radiopacket array
  char radiopacket[7] = "       ";
  radiopacket[0] = 'X'; //"N" 
  radiopacket[1] = tempNumChar[0];
  radiopacket[2] = tempNumChar[1];
  radiopacket[3] = tempNumChar[2];
  radiopacket[4] = tempNumChar[3];
  radiopacket[5] = tempNumChar[4];
 Serial.println(radiopacket);
 radiopacket[6] = 0;
 
  Serial.println("Sending..."); delay(10);

  //sends the [acket of data while indicating it sent using the LED
  if(rf95.send(radiopacket, 6))
  {
    digitalWrite(LED, HIGH);
  }
  
  digitalWrite(LED, LOW);
  Serial.println("Waiting for packet to complete..."); delay(10);
  rf95.waitPacketSent();
  
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
 
  Serial.println("Waiting for reply..."); delay(10);
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
  else
  {
    Serial.println("No reply, is there a listener around?");
  }
  delay(1000);
}

//function to grab the temperature data as a float 
float getTemp()
{
  sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  if(temp > -127 && temp <50){
  return temp;
  }
}
