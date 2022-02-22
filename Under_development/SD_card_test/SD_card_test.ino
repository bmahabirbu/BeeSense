// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include <RH_RF95.h>
#include "RTClib.h"

//for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3
#define RF95_FREQ 905.5
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Configuration that we'll store on disk
struct Config {
  const char* boardname;
  int time_to_send;
};

const char *filename = "config.txt";  // <- SD library uses 8.3 filenames
Config config;                         // <- global configuration object

// Loads the configuration from a file
void loadConfiguration(const char *filename, Config &config) {
  // Open file for reading
  File file = SD.open("config.txt");

  // Allocate the memory pool on the stack.
  // Don't forget to change the capacity to match your JSON document.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<96> doc;

  // Parse the root object
  DeserializationError error = deserializeJson(doc, file);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  // Copy values from the JsonObject to the Config
  config.boardname = doc["boardname"]; 
  config.time_to_send = doc["time_to_send"]; 
  

  // Close the file (File's destructor doesn't close the file)
  file.close();

  Serial.println(config.boardname);
  Serial.println(config.time_to_send);
}

// Prints the content of a file to the Serial
void printFile(const char *filename) {
  File myFile = SD.open("config.txt");
  if (myFile) {
    Serial.println("config.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening config.txt");
  }
}

void setup() {
  
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  
  setup_lora();
  
  setup_sd_card();
  
  //digitalWrite(8, LOW);
  //delay(30);
  
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Dump config file
  Serial.println(F("Print config file..."));
  printFile(filename);

  // Should load default config if run for the first time
  Serial.println(F("Loading configuration..."));
  loadConfiguration(filename, config);


}

void loop() {
  // not used in this example
}

void setup_lora(){
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  delay(100);

  Serial.println("Feather LoRa TX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    Serial.println("Uncomment '#define SERIAL_DEBUG' in RH_RF95.cpp for detailed debug info");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}

void setup_sd_card(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}
