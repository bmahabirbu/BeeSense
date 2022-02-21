void setup() {
  
  pinMode(13, OUTPUT);
  
   PCT2075 = Adafruit_PCT2075();
   
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Wait until serial port is opened
  
   setup_lora();
   setup_temp_humid();
   //setup_temp();
   setup_rtc();
   setup_ir();
   setup_gas();
  

  //fake mic set up
   randomSeed(analogRead(0));

}
