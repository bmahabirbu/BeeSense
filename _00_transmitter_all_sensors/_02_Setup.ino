void setup() {
  
   pinMode(13, OUTPUT);
   pinMode(8, OUTPUT);
   
   Serial.begin(115200);

   //for sd card first
   //lora_switch(false);
   //after ur done
   //lora_switch(true);
  
   setup_lora();
   setup_temp_humid();
   //setup_temp();
   setup_rtc();
   setup_ir();
   setup_gas();
   setup_sd_card();

   loadConfiguration(config);

   Serial.println(config.boardname);
   Serial.println(config.time_to_send);
 

}
