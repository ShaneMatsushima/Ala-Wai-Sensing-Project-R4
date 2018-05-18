#include <SPI.h>
#include <RH_RF95.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3
 
// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

#define ONE_WIRE_BUS 7

double temp;
 
// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

OneWire oneWire (ONE_WIRE_BUS);

DallasTemperature sensor(&oneWire);
 
void setup() 
{
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
 
  while (!Serial); // remove if not tethered to computer (looks for serial monitor to open)
  Serial.begin(9600);
  delay(100);
 
  Serial.println("Arduino LoRa TX Test!");
 
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
 
  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");
 
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
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
 
int16_t packetnum = 0;  // packet counter, we increment per xmission
 
void loop()
{
  Serial.println("Sending to rf95_server");
  // Send a message to rf95_server

  
  
  temp = getTemp();
  Serial.println(temp);
  String tempNumStr =  String(temp);
  Serial.println(tempNumStr);
  char tempNumChar[6];
  tempNumStr.toCharArray(tempNumChar, 6);
  Serial.println(tempNumChar);
  char radiopacket[6] = "      ";
  radiopacket[0] = tempNumChar[0];
  radiopacket[1] = tempNumChar[1];
  radiopacket[2] = tempNumChar[2];
  radiopacket[3] = tempNumChar[3];
  radiopacket[4] = tempNumChar[4];
 Serial.println(radiopacket);
 radiopacket[5] = 0;
  Serial.println("Sending..."); delay(10);
  rf95.send(radiopacket, 6);
 
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
float getTemp(){
    sensor.requestTemperatures();
  float temp = sensor.getTempCByIndex(0);
  if(temp > -127 && temp <50){
    return temp;
  }
}
