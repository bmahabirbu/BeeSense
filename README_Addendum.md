# Addendum

The Engineering Addendum is quick-start documentation written to any future team that may continue to work on your project. This is where you outline the gotchas of your project, types of things to look out for, the current state of the project, etc. The purpose of README.md is to save any future team weeks of detective work just to get to where you are today. Think back to what types of things you had wished you knew earlier, doing future teams a favor by passing that knowledge along.

## Current State of our Project
So far, we finalized our projects hardware and the sensors we use all work with out any hiccups in the software. We are using all off the shelf hardware parts so for groups who may continue our project the next steps might be to look into PCB design

For software our project main deliverables have been completed all bet with some quirks. The software can send and receive messages and can guarantee that those messages will be received. Sensor data readings can all be done with use using built in software modules edited by the group in the scripts. 

The csv and data analysis part of the project needs work. The data being saved to the csv has a weird format that should be correct once the data analysis algorithm is finalized. 

## Known errors for the project and things to look out for
The Lora sensor and the SD card does not play nice with the feather RFM925 microcontroller. Make sure to monitor the switching of the CS pin for using either the lora sensor or the sd card reader. Both cannot be used at the same time.

Be wary of updating the feather board via adafruits advice. A group member bricked a feather this way. On that not dont use python with the feather board it uses way to much power and python does not have good modules for power consumption.

The software does not use any cyber security encryption. Although lora is a relatively safe way to transmit data its never safe to transmit information without it being encrypted in some way.

## What we wished we knew
For software we wished we knew what sensors played nice with the type of microcontroller we were using. Our IEMS mic did not play nice and we had to scap the sensor in place of an analog mic. Documentation usually doesnt show what sensors arent supported with what microcontroller so best thing is to buy different types of sensors for each data unit one wants to measure.

We also wished we knew how hard it was to use lora with the packet cap at such a low amount of bytes per packet. Sending data like images or really big matrixes just wont work. You are very limited in what you can actually send. 
