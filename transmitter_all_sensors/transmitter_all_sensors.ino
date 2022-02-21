// All sensor test code
#include <SD.h>
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

//saves lines of file to list

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
