#define DALLAS_PIN 12
#define DHTPIN 5
#define DHTTYPE DHT22
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define BUFF_SIZE 50
#define MAX_STATIONS 2
#define BRING_KEYWORD "fetch\n"
#define MAIN_SENSORS_INTERVAL 3

#include <SoftwareSerial.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <Wire.h>
#include <SPI.h>

#include "RH_ASK.h"

#include "Station.h"
#include "Main.h"
#include "Second.h"
#include "Receiver.h"
#include "Bluetooth.h"
#include <TimeLib.h>
