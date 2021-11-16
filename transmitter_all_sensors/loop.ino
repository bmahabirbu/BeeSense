void loop() {
  
  packetnum++;
  
  String packetnum_str = "Packet number: "+String(packetnum);

  print_temp();
  print_rtc();
  print_ir();
  print_gas();
  //Fake mic code
  randNumber = random(1000,1500);
  Serial.print("Fake Mic val: ");
  Serial.println(randNumber);

  String temp_string = "TemperatureF*: ";
  String temp_num = String((PCT2075.getTemperature()*9/5)+32, 2);
  String temp_message = temp_string+temp_num;

  DateTime now = rtc.now();
  String date_year = String(now.year(), DEC);
  String date_month = String(now.month(), DEC);
  String date_day = String(now.day(), DEC);
  String date_hour = String(now.hour(), DEC);
  String date_min = String(now.minute(), DEC);
  String date_sec = String(now.second(), DEC);

  String date = "Date now: "+date_year+"/"+date_month+"/"+date_day+"/"+date_hour+":"+date_min+":"+date_sec;

  String pixel_str = String((pixels[0]*9/5)+32, 2);
  String ir_str = "First IR pixel temp in F: "+pixel_str;

  String eco2_str = String(sgp.eCO2);
  String TVOC_str = String(sgp.TVOC);
  String rawH2_str = String(sgp.rawH2);
  String rawEthanol_str = String(sgp.rawEthanol);
  String gas_str = "eCo2: "+eco2_str+" ppm, " + "TVOC: "+TVOC_str+" ppb, "+"Raw H2: "+rawH2_str+", "+"Raw Ethanol: "+rawEthanol_str;

  String noise_str = String(randNumber);
  String mic_str = "Fake mic noise: "+noise_str;

  String msg = packetnum_str+", "+temp_message+", "+date+", "+ir_str+", "+gas_str+", "+mic_str;
  send_message(msg);

  delay(3000);
    
}
