void setup() {
  
   pinMode(13, OUTPUT);
   pinMode(8, OUTPUT);
   
   Serial.begin(115200);

   while (!Serial) 
   {
    ; // wait for serial port to connect. Needed for native USB
   }

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
   Serial.print("Time_to_send: ");
   Serial.println(config.time_to_send);

   awk_name = "Package_Received_"+String(config.boardname);

   //Prototype2 delay
   Serial.println("First Standbye");
   delay(30000);
   
}

void loop() {
  
  packetnum++;
  
  String packetnum_str = String(packetnum);

  //print_temp();
  String temp_humid_str = print_temp_humid();
  String date = print_rtc();
  String ir_str = print_ir();
  String gas_str = print_gas();
  String mic_str = print_mic();

  String msg = config_str+", "+packetnum_str+", "+temp_humid_str+", "+date+", "+ir_str+" "+gas_str+", "+mic_str;
  send_message(msg);
  
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  int resend_count = 0;

  while (resend_count <= 5)
  {
    if (rf95.waitAvailableTimeout(1000))
    { 
      // Should be a reply message for us now   
      if (rf95.recv(buf, &len))
      {
        Serial.print("Got reply: ");
        String awk = String((char*)buf);
        awk = awk.substring(0,awk_name.length());
        Serial.println(awk);
        Serial.print("RSSI: ");
        Serial.println(rf95.lastRssi(), DEC);
        if (awk == awk_name)
        {
          Serial.println("Got correct awk!");
          break;
        }    
      }
      else
      {
        Serial.println("Receive failed");
        break;
      }
    }
    else
    {
      Serial.println("No reply, Resending packet");
      send_message(msg);
      resend_count = resend_count+1;
    }
  }

  
  log_data(msg);
  Serial.print("Standby mode"); 
  //Only use the lower power function without the need to see print statements 
  //LowPower.deepsleep(config.time_to_send*60*1000);
  delay(60000);
    
}
