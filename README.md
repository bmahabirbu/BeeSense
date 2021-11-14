# BeeSense
Sensior Design  Project about Monitoring Bees
Lora and Pi setup

Current functionality:
Feather m0 Rfm95 sends temp, rtc, IR cam (one pixel), gas data to pi
pi saves data to excel file
pi code launches automatically

Current set of functionalities to add:
* Allow for pi to distinguish between multiple boards
* SD card support
* Set time delay to send messages/board name from SD card
* Microphone support (unlikely there is a bug specific to SAMD)
* TCP to insure packages reach pi (reach goal for sure)
* Securtiy sending messages
