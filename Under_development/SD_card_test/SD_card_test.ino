/*
  Listfiles

  This example shows how print out the files in a
  directory on a SD card

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 8 fpr adsamd21

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 2 Feb 2014
  by Scott Fitzgerald

  This code will be modified to allow for reading
  and writing of scripts

  add lora to test switching capabilities

  //Set pin 8 high for use with SD card 
  //Set pin 8 low after finished with the sd card

  

*/
#include <SPI.h>
#include <SD.h>
#include <RH_RF95.h>

//for feather m0  
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 905.5

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

File root;

void setup() {
  pinMode(8, OUTPUT);
  lora_switch(false);
   
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  //switch cs pin
  lora_switch(true);
  
  //setup lora
  setup_lora();
  
  //switch cs pin
  lora_switch(false);
   
}

void loop() {
  
  //print sd card
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("done!");
  //switch cs pin
  lora_switch(true);
  
  //send message
  String msg = "Hellow world";
  send_message(msg);
  
  //switch cs pin
  lora_switch(false);
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
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

void lora_switch(bool flag) {
  if(flag == true){
    digitalWrite(8, LOW);
    delay(10);
  }
  else {
    digitalWrite(8, HIGH);
    delay(10);
  }
}
