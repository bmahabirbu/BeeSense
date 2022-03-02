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
        display.fill(0)
        prev_packet = packet
        packet_text = str(prev_packet, "utf-8")
        display.text('RX: ', 0, 0, 1)
        display.text("Message Received", 25, 0, 1)
        packet_array = packet_text.split(",")
        
        #print(float(packet_array[1].split(": ")[1]))
        #checks temperature
        if "sensor" in packet_array[0].split(": ")[1]:
            print("Checking temp: ")
            print(packet_array[3].split(": ")[1])
            if float(packet_array[3].split(": ")[1]) > 80.0:
                display.fill(0)
                print("Sending Email...")
                display.text("Sending Email...", 15, 0, 1)
                subprocess.call("ls", shell=True)
                subprocess.call("msmtp -t < message.txt", shell=True)
        
        try:
        
            with open("/media/pi/BEE_DRIVE/messages.csv", "a") as log:
                csv.writer(log).writerow(packet_array)
        except:
            print("Cant open usb to save excel file")

        print(packet_text)
        print("Sending return awk: ")
        awk = bytes("Package Received!\r\n","utf-8")
        rfm9x.send(awk)
        time.sleep(1)
        
    display.show()
    time.sleep(0.1)
