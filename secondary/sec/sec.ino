#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <RH_ASK.h>
#include <SPI.h> 
#include "LowPower.h"

#define DALLAS_PIN 4
#define DHTPIN 3
#define DHTTYPE DHT22
#define BUFF_SIZE 50 
#define ID 0

RH_ASK driver(1000, 12, 8, 0);

/* DHT 22 SETUP */
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);

  digitalWrite(7,HIGH);

  if (!driver.init())
    Serial.println("init failed");
  
  Serial.begin(9600);
  dht.begin();

}

void loop() 
{


  getAndSend();
  for(int i=0; i<=7; i++)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
//  delay(5000);

}

float getDallasTemp(DallasTemperature *sensors)
{
  float temp;
  /* Method That Gets And Returns Dallas Sensor Temperature */
  sensors -> requestTemperatures();
  temp = sensors->getTempCByIndex(0);

  if(temp != DEVICE_DISCONNECTED_C) 
    return temp;
  else
  {
      Serial.println("Error Could Not Read Dallas Temperature");
      return -300;
  }
}
float getDhtHumidity()
{
  float humidity = dht.readHumidity();

  if (humidity > 0 && humidity <= 100)
    return humidity;
  else
  {
    Serial.println("Error Reading DHT22 Humidity");
    return humidity ;
  }
}

void getAndSend()
{
    OneWire oneWire(DALLAS_PIN);

    DallasTemperature sensors(&oneWire);

 
    char toSend[BUFF_SIZE];
    float temp, humidity;
    digitalWrite(9,HIGH);

    delay(1000);
    sensors.begin();


    
    temp = getDallasTemp(&sensors);
    humidity = getDhtHumidity();

    sprintf(toSend, "%d %4d %4d",ID , (int) (round(temp * 10)), (int) round(humidity));

    
    driver.send((uint8_t *)toSend, strlen(toSend));
    driver.waitPacketSent();
        
    Serial.println(temp);
    Serial.println(humidity);
    Serial.println(toSend);
    digitalWrite(9,LOW);

}
