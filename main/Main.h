/*Dallas Setup*/
OneWire oneWire(DALLAS_PIN);
DallasTemperature sensors(&oneWire);

/* DHT 22 SETUP */
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP280 bmp; 
class Main: private Station
{

  public:
    int getDallasTemp()
    {
      return temp;   
    }
    

    int getDhtHumidity()
    {
      return humidity;
    }    
    
    int getBmpPressure()
    {
      return pressure;
    }
        
    int getBmpAlt()
    {
      return alt;
    }
    

    bool getSensorsData()
    {
        //Method That Gets And Sets Sensors Data

      sensors.requestTemperatures();
      temp = (int) round(sensors.getTempCByIndex(0) * 10);

      //Serial.print(sizeof(temp));
      if(temp == DEVICE_DISCONNECTED_C) 
       Serial.println(F("Error Could Not Read Dallas Temperature"));
      
      humidity = (int) round(dht.readHumidity());

      if (humidity < 0 || humidity > 100)
          Serial.println(F("Error Reading DHT22 Humidity"));
   
      pressure = (int) (bmp.readPressure() / 100);

      alt = round(bmp.readAltitude());
    }        

};
