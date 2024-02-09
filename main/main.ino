/*############################################################
# This is the code for the main station of the Arduino       #
# Weather Station.                                           #
#                                                            #
# Working Version 2.1.                                       #  
#                                                            #
# Desinged And Written Completely By George D. Papageorgiou. #
#                                                 June-2023  #
############################################################*/

#include "Definitions.h"

unsigned long lastDataTime = 0;
unsigned long secLastDataTime = 0;

Main mainStation;
Receiver re;
Secondary secStations[MAX_STATIONS];
Bluetooth ble;
Display disp;

void setup(void)
{
  
  sensors.begin(); // Start up Dallas Library
  dht.begin(); // Start up DHT22
  bmp.begin(0x76); //Start up bmp 280
  
  Serial.begin(9600); // Initialize Serial Port
  if (!driver.init())
    Serial.println("init failed");
    
  MyBlue.begin(9600); //initialize Bluetooth
  
  initializeStations(secStations); // Setting Initial Values In Secondary Stations Array
  Receiver::initializeReceived();
  
  disp.initializeDisp(); // Initialize Display  (Actually Displing Booting Screen)
  
  delay(1000);
}

void loop(void)
{
  unsigned long currentTime = now();
  

  if (re.get()) 
  { 
    // Get Incoming Values From All Stations
    
    Serial.println(F("Debug: Got Secondary Stations Data"));
    setStationsData(secStations);
    
    secLastDataTime = currentTime;
  }
  
  if(currentTime >= lastDataTime + MAIN_SENSORS_INTERVAL || lastDataTime == 0 )
  { 
    // IMPORTANT IF gathering, sending and displaying sensors data

   
    Serial.println(F("Debug: Got Main Station Data"));
    mainStation.getSensorsData();    
    disp.displayMainScreen(&mainStation);
    
    if(areSecondaries(secStations) && !secStations[0].areOutdated(currentTime, secLastDataTime))
      disp.updateSecondariesScreen(secStations);
    else
    {
      disp.clearLine(2);
      disp.clearLine(3);
      //Serial.println("in else");
    }
    lastDataTime = currentTime;

  }

  Bluetooth::readBlue(&mainStation, secStations); //Checking if the computer has asked for data

  delay(10);
}


void setStationsData(Secondary *st)
{
  int id;
  float temp, hum;

    Receiver::getReceivedData(&id, &temp, &hum);
    st[id].setId(id);
    st[id].setTemp(temp);
    st[id].setHumidity(hum);
}

void initializeStations(Secondary *st)
{
  for (int i = 0; i < MAX_STATIONS; i++)
  {
    st[i].setId(-3);
    st[i].setTemp(-300.0);
    st[i].setHumidity(-300.0);
  }
}

bool areSecondaries(Secondary *st)
{
  //FOR THIS VERSION WE HAVE ONLY ONE STATION WITH ID 0

  if(st[0].getId()==0)
    return true;
  else
    return false;
}
 

       
