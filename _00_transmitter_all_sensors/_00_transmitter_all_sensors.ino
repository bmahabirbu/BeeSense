// All sensor test code
#include <SD.h>
#include <ArduinoJson.h>
#include <ArduinoLowPower.h>
//Set pin 8 high for use with SD card 
//Set pin 8 low after finished with the sd card
#include <SPI.h>
#include <RH_RF95.h>
#include <Adafruit_PCT2075.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include "Adafruit_SGP30.h"
#include "RTClib.h"
#include <Adafruit_AHTX0.h>

//for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 905.5

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);
//keep track of packets sent
int packetnum = 0; 
int ref_min = 0;
int cur_min;

//sd cars stuff
struct Config {
  const char* boardname;
  const char* hivename;
  int time_to_send;
};
Config config;

String config_str;

//SD card initalizer
File myFile;

Adafruit_AHTX0 aht;
Adafruit_AMG88xx amg;
Adafruit_SGP30 sgp;
Adafruit_PCT2075 PCT2075;
RTC_PCF8523 rtc;
//for gas sensor
int counter = 0;
//for ir
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
//for rtc
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//function to get config from sd card
//function needs to be here for various compiler related issues
String loadConfiguration(Config &config) {

  //switch cs pin
  digitalWrite(8, HIGH);
  delay(30);
  
  // Open file for reading
  myFile = SD.open("config.txt");

  // Allocate the memory pool on the stack.
  // Don't forget to change the capacity to match your JSON document.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Parse the root object
  DeserializationError error = deserializeJson(doc, myFile);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return "Error";
  }

  // Copy values from the JsonObject to the Config
  config.boardname = doc["boardname"]; 
  config.hivename = doc["hivename"];
  config.time_to_send = doc["time_to_send"];

  String boardname_str = "Board name: "+String(config.boardname)+", ";
  String hivename_str = +"Hive name: "+String(config.hivename)+", ";
  String time_to_send_str = "Send message every: "+String(config.time_to_send)+" minutes";
  String config_str = boardname_str+hivename_str+time_to_send_str;
   
  // Close the file (File's destructor doesn't close the file)
  myFile.close();

  //switch cs pin
  digitalWrite(8, LOW);
  delay(30);

  return config_str;

  
}
