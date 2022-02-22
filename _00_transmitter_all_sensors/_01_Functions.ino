
void setup_temp_humid(){

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
}

String print_temp_humid(){
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print((temp.temperature*9/5)+32); Serial.println(" degrees F");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
  
  String temp_str = String((temp.temperature*9/5)+32, 2);
  String humid_str = String(humidity.relative_humidity, 2);
  String temp_humid_str = "Temperature F*: "+temp_str+", "+"Humidity %rH: "+humid_str;
  return temp_humid_str;
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

void setup_rtc() {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  Serial.println("RTC found!");

  rtc.start();
  float drift = 43; 
  float period_sec = (7 * 86400);  
  float deviation_ppm = (drift / period_sec * 1000000); 
  float drift_unit = 4.34; 
  // float drift_unit = 4.069; 
  int offset = round(deviation_ppm / drift_unit);
  // Un-comment to perform calibration once drift (seconds) and observation period (seconds) are correct
  // rtc.calibrate(PCF8523_TwoHours, offset); 
  // Un-comment to cancel previous calibration
  // rtc.calibrate(PCF8523_TwoHours, 0); 
  Serial.println("Offset is ");
  Serial.println(offset); // Print to control offset

  //un-comment to reset RTC
  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
}

String print_rtc() {
  DateTime now = rtc.now();
  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  String date_year = String(now.year(), DEC);
  String date_month = String(now.month(), DEC);
  String date_day = String(now.day(), DEC);
  String date_hour = String(now.hour(), DEC);
  String date_min = String(now.minute(), DEC);
  String date_sec = String(now.second(), DEC);
  String date = "Date now: "+date_year+"/"+date_month+"/"+date_day+"/"+date_hour+":"+date_min+":"+date_sec;

  return date;
  
}

void setup_gas() {
  Serial.println("SGP30 test");

  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

String print_gas() {
  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
     return "Raw Measurement failed";
  }
  Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");

  if (! sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return "Raw Measurement failed";
  }
  Serial.print("Raw H2 "); Serial.print(sgp.rawH2); Serial.print(" \t");
  Serial.print("Raw Ethanol "); Serial.print(sgp.rawEthanol); Serial.println("");

  String eco2_str = String(sgp.eCO2);
  String TVOC_str = String(sgp.TVOC);
  String rawH2_str = String(sgp.rawH2);
  String rawEthanol_str = String(sgp.rawEthanol);
  String gas_str = "eCo2: "+eco2_str+" ppm, " + "TVOC: "+TVOC_str+" ppb, "+"Raw H2: "+rawH2_str+", "+"Raw Ethanol: "+rawEthanol_str;
  
  return gas_str;
 
//  delay(1000);
//
//  counter++;
//  if (counter == 30) {
//    counter = 0;
//
//    uint16_t TVOC_base, eCO2_base;
//    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
//      Serial.println("Failed to get baseline readings");
//      return;
//    }
//    Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
//    Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
//  }

  
}

void setup_ir() {
   Serial.println(F("AMG88xx pixels"));

  bool status;
    
  // default settings
  status = amg.begin();
  if (!status) {
      Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      while (1);
  }
  
  Serial.println("-- Pixels Test --");
  Serial.println();
  delay(100); // let sensor boot up
}

String print_ir() {
   amg.readPixels(pixels);
   Serial.println("IR cam temp 8x8 array F*: ");
   Serial.print("[");
  for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
    Serial.print((pixels[i-1]*9/5)+32);
    Serial.print(", ");
    if( i%8 == 0 ) Serial.println();
  }
  Serial.println("]");
  Serial.println();

  String pixel_str = String((pixels[0]*9/5)+32, 2);
  String ir_str = "First IR pixel temp in F: "+pixel_str;

  return ir_str;
  
}

String print_mic() {
  // mic code
  int mic_value = analogRead(A0);
  
  Serial.print("Mic val: ");
  Serial.println(mic_value);

  String noise_str = String(mic_value);
  String mic_str = "mic noise: "+noise_str;

  return mic_str;

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
