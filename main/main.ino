#include "Definitions.h"

unsigned long lastDataTime = 0;


Main mainStation;
Receiver re;
Secondary secStations[MAX_STATIONS];
Bluetooth ble;

void setup(void)
{
  
  sensors.begin(); // Start up Dallas Library
  dht.begin(); // Start up DHT22
  bmp.begin(0x76);
  Serial.begin(9600); // Initialize Serial Port
  if (!driver.init())
    Serial.println("init failed");
  MyBlue.begin(9600);
  initializeStations(secStations);
  Receiver::initializeReceived();
  delay(1000);
}

void loop(void)
{
  unsigned long currentTime = now();

  if (re.get())
  { // Get Incoming Values From All Stations

    Serial.println(F("Debug: Got Secondary Stations Data"));
    setStationsData(secStations);
  }
  if(currentTime >= lastDataTime + MAIN_SENSORS_INTERVAL)
  {
    Serial.println(F("Debug: Got Main Station Data"));
    mainStation.getSensorsData();
    lastDataTime = currentTime;
  }

  Bluetooth::readBlue(&mainStation, secStations);

  delay(100);
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
    st[i].setTemp(-300.0);
    st[i].setHumidity(-300.0);
  }

}       