# SPDX-FileCopyrightText: 2018 Brent Rubell for Adafruit Industries
#
# SPDX-License-Identifier: MIT

"""
Example for using the RFM9x Radio with Raspberry Pi.

Learn Guide: https://learn.adafruit.com/lora-and-lorawan-for-raspberry-pi
Author: Brian Mahabir
"""
# Import Python System Libraries
import time
import csv
import os
import numpy as np
import pandas as pd
import subprocess
from time import strftime
# Import Blinka Libraries
import busio
from digitalio import DigitalInOut, Direction, Pull
import board
# Import the SSD1306 module.
import adafruit_ssd1306
# Import RFM9x
import adafruit_rfm9x
#Header column names for CSV
HEADER_CSV = ["Board name", "Hive name", "Packet number", "Temperature in F", "Humidity %rH", "IR Pixel Temp in F",
              "eCo2 (ppm)", "TVOC (ppb)","Raw H2",
              "Raw Ethanol", "Mic Noise", "Weight (lbs)",]

# Button A
btnA = DigitalInOut(board.D5)
btnA.direction = Direction.INPUT
btnA.pull = Pull.UP

# Create the I2C interface.
i2c = busio.I2C(board.SCL, board.SDA)

# 128x32 OLED Display
reset_pin = DigitalInOut(board.D4)
display = adafruit_ssd1306.SSD1306_I2C(128, 32, i2c, reset=reset_pin)
# Clear the display.
display.fill(0)
display.show()
width = display.width
height = display.height

# Configure LoRa Radio
CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, 905.5)
rfm9x.tx_power = 23
prev_packet = None
print('Lora Ready')
while True:
    packet = None
    # draw a box to clear the image
    display.fill(0)
    display.text('RasPi LoRa', 35, 0, 1)
    
    if not btnA.value:
        #safe shutdown
        display.fill(0)
        print("Safe Shutdown in now...")
        display.text("Safe Shutdown in now...", 15, 0, 1)
        time.sleep(0.5)
        subprocess.call("sudo shutdown now", shell=True)

    # check for packet rx
    packet = rfm9x.receive()
    if packet is None:
        display.show()
        display.text('- Waiting for PKT -', 15, 20, 1)
    else:
        # Display the packet text and rssi
        try: 
            display.fill(0)
            prev_packet = packet
            packet_text = str(prev_packet, "utf-8")
            display.text('RX: ', 0, 0, 1)
            display.text("Message Received", 25, 0, 1)
            packet_array = packet_text.split(",")
        except:
            continue
        
        #print(float(packet_array[1].split(": ")[1]))
        #checks temperature
        boardname = packet_array[0]
        if "sensor" in boardname:
            weight_sensor = False;
            print("Checking temp: ")
            print(packet_array[3])
            if float(packet_array[3]) > 80.0:
                display.fill(0)
                print("Sending Email...")
                display.text("Sending Email...", 15, 0, 1)
                subprocess.call("ls", shell=True)
                subprocess.call("msmtp -t < message.txt", shell=True)
        else:
            weight_sensor = True;
            
        try:
            if not os.path.isfile("/media/pi/BEE_DRIVE/messages.csv"):
                print ("No CSV file creating one ...")
                try:
                    df = pd.DataFrame(columns=HEADER_CSV)
                    df.to_csv("/media/pi/BEE_DRIVE/messages.csv", index=False)
                except:
                    print("Error creating csv file!")
            
            if weight_sensor == True :
                print("writing weight sensor data to csv")
                csv_input = pd.read_csv("/media/pi/BEE_DRIVE/messages.csv")
                csv_input.at[packet_array[2],'Weight (lbs)'] = packet_array[3]
                csv_input.to_csv("/media/pi/BEE_DRIVE/messages.csv", index=False)
            else:
                print("writing sensor data to csv")
                with open("/media/pi/BEE_DRIVE/messages.csv", "a", newline='') as log:
                    csv.writer(log).writerow(packet_array)
                log.close();
                
        except:
            print("Cant open usb to save excel file")

        print(packet_text)
        awk = bytes("Package_Received_"+str(boardname),"utf-8")
        print("Sending return awk: ")
        print(awk)
        rfm9x.send(awk)
        
    display.show()
    time.sleep(0.1)
