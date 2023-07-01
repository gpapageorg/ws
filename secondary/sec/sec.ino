#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <RH_ASK.h>
#include <SPI.h> 

#define DALLAS_PIN 4
#define DHTPIN 3
#define DHTTYPE DHT22
#define BUFF_SIZE 50 
#define ID 1

RH_ASK driver(1000, 9, 8, 0);

/*Dallas Setup*/
OneWire oneWire(DALLAS_PIN);
DallasTemperature sensors(&oneWire);

/* DHT 22 SETUP */
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7,HIGH);
  
  delay(500);

  sensors.begin(); // Start up Dallas Library
  dht.begin(); // Start up DHT22

  if (!driver.init())
	Serial.println("init failed");

  Serial.begin(9600);

}

void loop() 
{
  char word[BUFF_SIZE];

  float temp, humidity;

  temp = getDallasTemp();
  humidity = getDhtHumidity();
  
  sprintf(word, "%d %4d %4d",ID , (int) (temp * 100), (int) (humidity * 100));
  Serial.println(temp);
  Serial.println(humidity);
  Serial.println(word);
  


  driver.send((uint8_t *)word, strlen(word));
	driver.waitPacketSent();

  delay(5000);

}

float getDallasTemp()
{
  float temp;
  /* Method That Gets And Returns Dallas Sensor Temperature */
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);

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
    return -300;
  }
}  

