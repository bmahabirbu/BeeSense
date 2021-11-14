void loop() {
  //code to loop though different messages
  if(packetnum == 5)
  {
    packetnum = 0;
  }

  print_temp();
  print_rtc();
  print_ir();
  print_gas();
  //Fake mic code
  randNumber = random(1000,1500);
  Serial.print("Fake Mic val: ");
  Serial.println(randNumber);

  //send temp
  if(packetnum == 0)
  {
    String temp_string = "TemperatureC*: ";
    String temp_num = String(PCT2075.getTemperature(), 2);
    String temp_message = temp_string+temp_num;
    send_message(temp_message);
  }
  
  if(packetnum == 1)
  {
    DateTime now = rtc.now();
    String date_year = String(now.year(), DEC);
    String date_month = String(now.month(), DEC);
    String date_day = String(now.day(), DEC);
    String date_hour = String(now.hour(), DEC);
    String date_min = String(now.minute(), DEC);
    String date_sec = String(now.second(), DEC);

    String date = "Date now: "+date_year+"/"+date_month+"/"+date_day+"/"+date_hour+":"+date_min+":"+date_sec;
    send_message(date);
  }
  if(packetnum == 2)
  {
    String pixel_str = String(pixels[0], 2);
    String ir_str = "First pixel temp: "+pixel_str;
    send_message(ir_str);
  }
  if(packetnum == 3)
  {
    String eco2_str = String(sgp.eCO2);
    String gas_str = "eCo2: "+eco2_str+" ppm";
    send_message(gas_str);
  }
  if(packetnum == 4)
  {
    String noise_str = String(randNumber);
    String mic_str = "Fake mic noise: "+noise_str;
    send_message(mic_str);
  }

  packetnum++;

  delay(1000);
    
}
