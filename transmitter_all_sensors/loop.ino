void loop() {
  
  packetnum++;
  
  String packetnum_str = "Packet number: "+String(packetnum);

  //print_temp();
  String temp_humid_str = print_temp_humid();
  String date = print_rtc();
  String ir_str = print_ir();
  String gas_str = print_gas();
  String mic_str = print_mic();

  //set specfic times when to send message

  String msg = packetnum_str+", "+temp_humid_str+", "+date+", "+ir_str+", "+gas_str+", "+mic_str;
  send_message(msg);

  log_data(msg);

  delay(3000);
 
    
}
