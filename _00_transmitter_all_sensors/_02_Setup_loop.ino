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
   config_str = loadConfiguration(config);
   Serial.println(config_str);

  //Prototype2 delay
   delay(30000);
   Serial.println("First Standbye");
}

void loop() {
  
  packetnum++;
  
  String packetnum_str = "Packet number: "+String(packetnum);

  //print_temp();
  String temp_humid_str = print_temp_humid();
  String date = print_rtc();
  String ir_str = print_ir();
  String gas_str = print_gas();
  String mic_str = print_mic();

  String msg = config_str+", "+packetnum_str+", "+temp_humid_str+", "+date+", "+ir_str+", "+gas_str+", "+mic_str;
  send_message(msg);
  log_data(msg);
  Serial.print("Standby mode");
  //Only use the lower power function without the need to see print statements 
  //LowPower.deepsleep(config.time_to_send*60*1000);
  delay(60000);
    
}
