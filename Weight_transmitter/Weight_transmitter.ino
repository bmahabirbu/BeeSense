
#include "HX711.h"
#include <SD.h>
#include <ArduinoJson.h>
#include <ArduinoLowPower.h>
#include <SPI.h>
#include <RH_RF95.h>

//for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 905.5

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

//sd card stuff
struct Config {
  const char* boardname;
  const char* hivename;
  int time_to_send;
};
Config config;
String config_str;

//SD card initalizer
File myFile;

//how many readings to take
int weight_time = 20;
//weight readings
float weights;
float avg_weights;

int packetnum;

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  6
#define CLK  5

HX711 scale;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
   
  Serial.begin(9600);
  Serial.println("Weight scale Lora sensor board code");

  setup_lora();
  setup_sd_card();

  config_str = loadConfiguration(config);

  Serial.println(config.boardname);
  Serial.println(config.time_to_send);

  setup_weightscale();
  
}

void loop() {
  
  packetnum++;
  String packetnum_str = "Packet number: "+String(packetnum);
  String weight_str = print_weightscale();
  String msg = config_str+", "+packetnum_str+", "+weight_str;
  send_message(msg);
  log_data(msg);
  //Only use the lower power function without the need to see print statements 
  //LowPower.deepsleep(config.time_to_send*60*1000);
  delay(18000);
  

}


//LORA



void setup_lora(){
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  delay(1000);

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

void send_message(String string){
  delay(1000); // Wait 1 second between transmits, could also 'sleep' here!
  digitalWrite(13, HIGH); //LED high
  Serial.println("Transmitting..."); // Send a message to rf95_server
  String radiopacket = string;
  Serial.println("Sending...");
  Serial.println(string);
  delay(10);
  rf95.send((uint8_t *)radiopacket.c_str(),radiopacket.length());

  Serial.println("Waiting for packet to complete..."); 
  delay(10);
  rf95.waitPacketSent();
  digitalWrite(13, LOW);//LED off
}



//SD CARD



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

  String boardname_str = "Board name: "+String(config.boardname);
  String hivename_str = +"Hive name: "+String(config.hivename);
  //String time_to_send_str = "Send message every: "+String(config.time_to_send)+" minutes";
  String config_str = boardname_str+", "+hivename_str;
  

  // Close the file (File's destructor doesn't close the file)
  myFile.close();

  //switch cs pin
  digitalWrite(8, LOW);
  delay(30);

  return config_str;
}

void setup_sd_card(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void lora_switch(bool flag) {
  if(flag == true){
    digitalWrite(8, LOW);
    delay(30);
  }
  else {
    digitalWrite(8, HIGH);
    delay(30);
  }
}

void log_data(String msg){

  //switch cs pin
  lora_switch(false);
  
   // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("log.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to log.txt...");
    myFile.println(msg);
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening log.txt");
  }

  //switch cs pin
  lora_switch(true);

}


//WEIGHT


void setup_weightscale(){
  
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
  
}

String print_weightscale(){
  for (int i = 0; i < weight_time; i++)
  {
    Serial.print("Reading: ");
    Serial.print(scale.get_units(), 1); //scale.get_units() returns a float
    weights = weights+scale.get_units();
    Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
  }

  avg_weights = weights/100;
  
  String avg_weights_str = String(avg_weights);
  String weight_str = "weight in lbs is : "+avg_weights_str;
  
  return weight_str;
  
  
}
