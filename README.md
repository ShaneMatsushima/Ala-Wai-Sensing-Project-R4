# Ala-Wai-Sensing-Project-R4
## Project Synopsis
This Project is used for collecting data from the Ala Wai using our small device consisting of a temperature sensor, NodeMCU, and the LoRa Feather 32u4. The data is then placed into a google sheet that is keeping and recording the data to look at later. The Google Sheets also puts the data into a graph to see the change over a period of time. 

This is one of many projects that is monitoring the Ala Wai watershed. This project is helping the group of scientists, teachers, and students apart of the [Na Wai 'Ekolu](https://www.nawaiekolu.org/). This overarching project is to inspire and get citixen research out there to create a database for watershed helth and even watershed biodiversity. This data collecting project will be used along multiple areas on the Ala Wai to get a better understanding on the change in enviorment throught the island. 

## Getting Started
This section describes the nmaterials and software needed to create this project. These are just the basic needs to create the temperature collecting monitoring system. Other software and sensors can be added if needed. 
### Materials Needed
These are the supplies needed to create this project: 
* Temperature sensor which can be found here: [Temperature Sensor](https://www.sparkfun.com/products/11050)
* LoRa Feather 32u4 which can be found here: [LoRa Feather](https://www.adafruit.com/product/3078)
* NodeMCU which can be found here: [NodeMCU](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010O1G1ES)
* Water tiight container which can be found here: [Container](https://www.mcmaster.com/#electrical-enclosures/=1bru0h2)

### Prerequisites
The prerequisities for this project consist of libraries, an IDE (Integrated Development Enviroment), and a website account that will be used to hold the data coming from the mounted monitoring system. The project also requires that the electronics (more specifically the NodeMCU) has a WiFi network to connect to.

For an IoT (Internet of Things) interface, we used [Ubidots](https://ubidots.com/education/) to create a platform for the data collected
from the monitoring system (mainly temperature) into a clean space where teachers and students can see the real time data. With this website, we use it as a house point for the incoming data to be stored so that google sheets can grab this data and place it into table that keep a running history of the data. 

Here is the IDE needed to upload and change code for this project:

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)

The following librairies can be found through the following path: Source/LoRa_Project/Libraries
* OneWire Library
* Dallas Temperature Library
* Radio Head Library
* Ubidots Libarry

## Basic Setup
### Installing the main code
To install the main code, click on the top right corner of the GitHub that says "Clone or download" and download the whole file as a .zip. This will allow you to download all the main code that will be uploaded to the different electronics and all the libraires can be downloaded from the file. 

### Installing and setting up Arduino IDE
First, install the IDE (the link can be found in the prerequisites section). Once that is done, follow the steps bellow to configure the IDE to upload to the different boards with the proper libraries installed.
* Open Arduino IDE 
* Go to File -> Prefrence
* Under the "Additional Boards Manager URLs" paste this link: "https://adafruit.github.io/arduino-board-index/package_adafruit_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json" 
* Then press OK on the bottom right corner of that page
* Go to Tools -> Board -> Boards Manager
* In the search box look up "Adafruit AVR" and install that profile (This is the board profile used to upload to the LoRa Feather)
* Once it's done downloading, search for "esp8266 by esp8266 community" and download that profile (This is the board profile used to upload to the NodeMCU)
After all the steps above have been done, the IDE is setup and ready to upload the the designated boards. The following steps will help place the libararies needed in the right area:
* Download the main code file on GitHub (This instruction can be found in the prerequisites)
* Then to locate the library file for Arduino:
For Window users:
* Documents -> Arduino -> Library
* Place the libarries downloaded form the main source file into the Arduino library file
Once this is done, the libraries are installed and ready to be used. 

### Setting up Ubidots
Ubidots is an IoT website that allows data to be sent to it and monitored from any device connected to the internet. Follow the following steps to create an account in Ubidots. This will also show how to create devices and variables that will be used in the project. 
* Go to the Ubidots [Education website](https://ubidots.com/education/) and click Sign Up
* Enter a vaid email, Username, and Password 
Once an account is created, there will be a blank page with three diffrent tabs.
* Click on the "Devices" tab 
* Click on Add Device (Note: Name the device based on the project. e.g LoRa Temp)
* Click on Add Variable 
* Name the variable created Temperature
Once the device and variable is created, Ubidots is setup. But will be reffered to to input data into the code to allow the NodeMCU to send data over to Ubidots and for Ubidots to send data over to google sheets. 

## Coding
### Loading the Code
All the code that will be going on the electronics have been premade. Varaibles and changes that are needed from the user is signalled in the comments of the code. To load the main code, follow these steps so that we can upload the code to the electronics.
#### LoRa Feather 32u4 Transmitting Code
* Go to the file downloaded in the prerequisistes 
* Go to Source -> LoRa Project -> Transmit -> LoRa_Feather_Master.ino 
* Open the .ino file in Arduino and the code is ready to be uploaded
#### LoRa Feather 32u4 Receiving Code
* Go to the file downloaded in the prerequisites
* Go to Source -> LoRa Project -> Receive -> LoRa_Feather_Receive_Matser.ino
* Open the .ino file in Arduino and the code is ready to be uploaded 
#### NodeMCU Sending Code
* Go to the file downloaded in the prerequisites
* Go to Source -> LoRa Project -> Sending -> NodeMCU_Send_Code.ino
* Open the .ino file in Arduino and the code is ready to be used 

### Uploading Code
Once the code is open in the IDE, the following steps will showcase how to upload code to each board
#### LoRa Feather 32u4 Transmitting Upload
*Note Before uploading code, check the code comments to see what variables need to be change* 
* Go to Tools -> Boards and scroll down untill Feather 32u4 shows up
* Click on that board 
* Plug in the Feather via Micro USB to USB data cable into the computer
* Go to Tools -> Comm Ports and click on port the board is plugged into 
* Press the upload button on the top left corner of the IDE
*Note: uploading to the board may take time*
#### LoRa Feather 32u4 Receiving Upload
*Note Before uploading code, check the code comments to see what variables need to be change* 
* Using the receiving code for the LoRa Feather, follow the same steps in the Transmitting Upload step
#### NodeMCU Sending Upload
##### Changing Variables in Code
*Note Before uploading code, check the code comments to see what variables need to be change* 
To find the Token for the code:
* Go to Ubidots and click on your profile
* Click on API Credentials
* Copy the Token and place it into the respected area of the code
To find the variable ID for the code:
* Go to Devices -> Variables
* Click on the varaible "temperature" and click on the i icon
* Copy the Variable ID and place it into the respected area of the code
Replace the WIFIUSERNAME and WIFIPASSWORD with the network security settings that the NodemCU will be connecting to
##### Changing Devices and Uploading Code
Once the variables have been changed to it's respected ID's, the following will help upload the code to the NodeMCU
* Go to Tools -> Boards -> 1.0 NodeMCU and click on that device
* Plug in the NodeMCU via Micro USB to USB into a Comm Port
* Select the Comm Port the device is in and click the upload button on the top right of the IDE

### Wiring
Follow the schematics for the wiring of both the transmitting and receiving portions of the system. 

