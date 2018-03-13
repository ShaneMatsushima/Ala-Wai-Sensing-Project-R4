/*This Code sends the data using an array instead of every minute
 * The Electron grabs temperature every minute and stores it into the deisgnated array
 * After grabbing an hour of temperature data, it will turn on the cellular and send the data in an array format
 * Note: still in progress code, Using strings instead of array for now
*/ 
 // This #include statement was automatically added by the Particle IDE.
#include "OneWire.h"


#include "spark-dallas-temperature.h"

#include "application.h"

#define ONE_WIRE_BUS D3
#define ONE_DAY_MILLIS (24 60 60 * 1000)
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

char resultstr[64]; //String to store the sensor temp
char voltagestr[64]; //String to store the voltage
char chargestr[64]; //String to store the charge
char cellularstr[64];
char timestr[64];
char stupidlyLongStr[64]="";
char voltstr[64] = "";

float raw = 0;
float final = 0;

double dataArray[60];
double voltArray[60];

char gstArray[60][64];
char gsvArray[60][64];

FuelGauge fuel;

void setup()
{

    Serial.begin(9600);
    //declare particle variables:
    Particle.variable("temp", stupidlyLongStr, STRING);
    Particle.variable("voltage", voltstr, STRING);
    Particle.variable("time", timestr, STRING);
    //Particle.variable("soC", chargestr, STRING);
    //Particle.variable("cellStrength", cellularstr, STRING);
    //begins temperature sensor
    sensors.begin();

}


void loop()
{
    //connects particle to cellular
    //Cellular.on();
    //Cellular.connect();
    Particle.connect();
    Particle.connected();
    
    
   // for(int i = 0; i <5; i++){
        //get data from sensor systems
        getTemp();
        getVoltage();
        //getCharge();
        //getCellSignal();
        if( fuel.getVCell() <= 3.0){
            sprintf(voltagestr, "%s", "Shutting down");
        }
        //published data onto particle cloud for testing purposes
        Particle.publish("temp", String(resultstr), PRIVATE);
       delay(60000);
   // }
    if( fuel.getVCell() <= 3.0){
        Cellular.off();
        System.sleep(SLEEP_MODE_DEEP);
    }

    //disconnects from cellular and leaves electron in least energy consuming mode
    //this portion is commmented out so that the Electorn will send data once minute 
   // Cellular.off();
   // System.sleep(SLEEP_MODE_DEEP,3300); //3300
}

//gets temperature in degrees celcius and sets it to particle variable
void getTemp(){
    float temp;
    sensors.requestTemperatures();
    /* this is the averaging code (Work in progress)
    raw = 0;
    for(int i = 0; i < 1; i++){
       float temp = sensors.getTempCByIndex(0);
       raw += temp;
       delay(1000);
    }
    final = raw/5; 
    
    int temp1 = (final - (int)final) * 100;
    if(final > -127 && final<85){
        char tempInChar[32];
        sprintf(tempInChar,"%0d.%d", (int)final, temp1);
        //google docs will get this variable - if you are storing the value in a google sheet
        sprintf(resultstr, "%s", tempInChar);
    }
    final = 0;
    raw = 0;
    */
    for (int i = 1; 1 <= 60; i++){
    temp = sensors.getTempCByIndex(0);
    dataArray[i] = temp;
    }
    
    for (int x = 1; 1 <= 60; x++){
    if(dataArray[x] > -127 && dataArray[x]<85){
        int temp1 = (dataArray[x] - (int)dataArray[x]) * 100;
        char tempInChar[32];
      sprintf(tempInChar,"%0d.%d", (int)dataArray[x], temp1);
        //google docs will get this variable - if you are storing the value in a google sheet
       sprintf(resultstr, "%s", tempInChar);
       strncat(stupidlyLongStr, resultstr, 2048);
       strncat(stupidlyLongStr, "~", 2048);
    }
    
}
}
//grabs voltage in volts and sets it to particle variable
void getVoltage(){
    float voltage;
    for (int y = 1; 1<= 60; y++){
     voltage = fuel.getVCell();
    voltArray[y] = voltage;
}
    for (int x = 1; 1 <= 60; x++){
    int voltage1 = (voltArray[x] - (int)voltArray[x]) * 100;
    char voltageInChar[32];
    sprintf(voltageInChar,"%0d.%d", (int)voltArray[x], voltage1);
    //google docs will get this variable - if you are storing the value in a google sheet
    sprintf(voltagestr, "%s", voltageInChar);
       strncat(voltstr, voltagestr, 2048);
       strncat(voltstr, "~", 2048);
    }
}
//Grabs charge in percentage and sets it to particle variable
/*
void getCharge(){
    
    float charge = fuel.getSoC();
    int charge1 = (charge - (int)charge) * 100;
    char chargeInChar[32];
    sprintf(chargeInChar,"%0d.%d", (int)charge, charge1);
    //google docs will get this variable - if you are storing the value in a google sheet
    strncat(chargeInChar, "%", 1);
    sprintf(chargestr, "%s", chargeInChar);
}
void getCellSignal(){
    int rssi = 0;
    int bars = 0;
    CellularSignal sig = Cellular.RSSI();
    rssi = sig.rssi;
    if (rssi < 0) {
        if (rssi >= -57) {sprintf(cellularstr, "%s", "☻☻☻☻☻");}
        else if (rssi > -68) {sprintf(cellularstr, "%s", "☻☻☻☻☺");}
        else if (rssi > -80) {sprintf(cellularstr, "%s", "☻☻☻☺☺");}
        else if (rssi > -92) {sprintf(cellularstr, "%s", "☻☻☺☺☺");}
        else if (rssi > -104) {sprintf(cellularstr, "%s", "☻☺☺☺☺");}
    }
}
*/
