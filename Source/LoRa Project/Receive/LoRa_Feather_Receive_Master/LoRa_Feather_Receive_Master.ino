/**
 * Created By: Shane Matsushima
 * Date: 12/12/18
 * Purpose: The purpose for this code is to receive the transmitting data from the other RFM and relay it into a NodeMCU
 *          which will send the data over to Ubidots. This code utilises the LoRa RFM transciever and an Arduino Uno to 
 *          push and get data from one system to aother. This is the middle man for the transmition of data. 
 */

//Libraries declared for use
#include <SPI.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>

//Declares that pins 10 & 11 are now RX & TX on the Feather
SoftwareSerial mySerial(10,11); //rx, tx

//Defining pins that the LoRa breakout baord uses
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7


 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);
 
// Blink on receipt
#define LED 13

void setup() 
{
  //connects LED pin to an output (LED is an output)
  pinMode(LED, OUTPUT);     
  pinMode(RFM95_RST, OUTPUT);
  
  digitalWrite(RFM95_RST, HIGH);
  
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(5000);
 

  
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
 
  while (!rf95.init()) {
    Serial.println("init failed");
    while (1);
  }

 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFreq failed");
    while (1);
  }

  Serial.println("Ok");

 
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
 
  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}
 
void loop() {
  //checks to see if a packet was sent over from the transmitting side
  if (rf95.available())
  {  
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    //if the packet was sent with the correct buf and len
    if (rf95.recv(buf, &len))
    {
    uint8_t num[6];

    for (int i = 0; i < 6; i++) {
      num[i] = buf[i+1];
    }

    char sensorNum = buf[0];
   
      //turns LED on to indicate packet was received
      digitalWrite(LED, HIGH);

      //converts the data received into a string 
      String val1 = (char*)num;

      //checks to see if the indicated stream was collected based on the beginning character
     //if(tempval[0] == 'X'){ //change this character based on the stream character on the transmitting side
      Serial.println(val1);
      Serial.println(sensorNum);

     //send the string data over RX and TX to the NodeMCU
     mySerial.print(val1 + sensorNum);
     
     
      // Send a reply
      uint8_t data[] = "bruh";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      digitalWrite(LED, LOW);
    }
    else
    {
    }
  }
}
