# Ala-Wai-Sensing-Project-R4
## Project Synopsis
This Project is used for collecting data from the Ala Wai using our small device consisting of a temperature sensor and a Particle Electron. The data is then placed into a google sheet that is keeping and recording the data to look at later. The Google Sheets also puts the data into a graph to see the change over a period of time. This project sends temperature data once a minute till the battery voltage for the electron is around 3.0v, then the Electron will go into deep sleep. 

This is one of many projects that is monitoring the Ala Wai watershed. This project is helping the group of scientists, teachers, and students apart of the [Na Wai 'Ekolu](https://www.nawaiekolu.org/). This overarching project is to inspire and get citixen research out there to create a database for watershed helth and even watershed biodiversity. This data collecting project will be used along multiple areas on the Ala Wai to get a better understanding on the change in enviorment throught the island. 

## Getting Started
This section describes the nmaterials and software needed to create this project. These are just the basic needs to create the temperature collecting monitoring system. Other software and sensors can be added if needed. 
### Materials Needed
These are the supplies needed to create this project: 
* Temperature sensor which can be found here: [Temperature Sensor](https://www.sparkfun.com/products/11050)
* LiPo battery (voltage around 3.3v - 4.0v) 
* Water tiight container which can be found here: [Container](https://www.mcmaster.com/#electrical-enclosures/=1bru0h2)

### Prerequisites
This IoT (Internet of Things) project is based on using Particles' IDE and the server that allows you to send data from your Partilce Electron to the webhook or the erver that will send your data. For this project we are using Particles' partnership with google to send data from the Electron to google sheets. The temperature and voltage data is sent to the google sheets. On google sheets side, the time stamp is created and the graph is produced based on what data is being collected from the Electron. 

Here is the libraries needed in order to use the code:
* [OneWire Library](https://github.com/PaulStoffregen/OneWire)
* [Dallas Temperature Library](https://github.com/milesburton/Arduino-Temperature-Control-Library)

## Basic Setup





