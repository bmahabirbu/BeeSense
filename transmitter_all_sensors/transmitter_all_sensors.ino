// All sensor test code
// Code to switch pin 8 for lora/sd card
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

int packetnum = 0; 

Adafruit_AHTX0 aht;
Adafruit_AMG88xx amg;
Adafruit_SGP30 sgp;
Adafruit_PCT2075 PCT2075;
RTC_PCF8523 rtc;
//for gas sensor
int counter = 0;
//for mic
long randNumber;
//not needed
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}
//for ir
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
//for rtc
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
