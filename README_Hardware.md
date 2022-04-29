# Hardware MD
## <ins>Schematics:</ins>
### <ins>Block Diagrams:</ins>
1. Overall system summary:

![System Summary](./assets/System%20Summary.png)

2. Sensor board block diagram:

![Sensor Board](./assets/Sensor%20Board%20Block%20Diagram.png)

3. Scale block diagram:

![Scale](./assets/Scale%20Block%20Diagram.png)

### <ins>Scale Wiring Diagram:</ins>

![Scale Wiring](./assets/Scale%20Wiring.png)

## <ins>Vendor Info + Bill of Materials:</ins>

| Item | Description | Vendor | Cost |
| ---- | ----------- | ------ | ---- |
| Sensor Board (x1) |
| 1 | LoRa Feather 900MHz | Adafruit | $34.99 |
| 2 | Adalogger | Adafruit | ---- |
| 3 | Temperature Humidity Sensor | Adafruit | ---- |
| 4 | Air Quality Sensor | Adafruit | ---- |
| 5 | ----------- | Adafruit | ---- |
| 6 | ----------- | Adafruit | ---- |
| 7 | ----------- | MicroCenter | ---- |
| 8 | ----------- | Adafruit | ---- |
| 9 | ----------- | Adafruit | ---- |
| 10 | ----------- | Adafruit | ---- |
| 11 | ----------- | Adafruit | ---- |
| 12 | ----------- | Adafruit | ---- |
| 13 | ----------- | Adafruit | ---- |
| Scale (x1) |
| 14 | ----------- | ------ | ---- |
| 15 | ----------- | ------ | ---- |
| 16 | ----------- | ------ | ---- |
| 17 | ----------- | ------ | ---- |
| 18 | ----------- | ------ | ---- |
| 19 | ----------- | ------ | ---- |
| 20 | ----------- | ------ | ---- |
| 21 | ----------- | ------ | ---- |
| 22 | ----------- | ------ | ---- |
| LoRa Gateway |
| 23 | ----------- | ------ | ---- |
| 24 | ----------- | ------ | ---- |
| 25 | ----------- | ------ | ---- |
| 26 | ----------- | ------ | ---- |
| 27 | ----------- | ------ | ---- |
|  | Total Cost |  | $350.84 |

## <ins>References:</ins>
* We used the Adafruit guide for the LoRa feather to figure out power requirements along with the radio datasheets. Links: https://cdn-shop.adafruit.com/product-files/3179/sx1276_77_78_79.pdf; https://cdn-shop.adafruit.com/product-files/3179/sx1276_77_78_79.pdf; https://learn.adafruit.com/adafruit-feather-m0-radio-with-lora-radio-module/overview
* We used the MAX9814 datasheet to find power requirements. Link: https://learn.adafruit.com/adafruit-feather-m0-radio-with-lora-radio-module/overview
* We used the directions on the Adafruit MAX9814 webpage as a guide to solder the microphone. Link: https://learn.adafruit.com/adafruit-agc-electret-microphone-amplifier-max9814/
* We used the Adafruit guide for the datalogger to find power requirements. Link: https://learn.adafruit.com/adafruit-adalogger-featherwing/downloads
* We used the AHT20 datasheet to find power requirements. Link: https://learn.adafruit.com/adafruit-adalogger-featherwing/downloads
* We used the SGP30 datasheet to find power requirements. Link: https://cdn-learn.adafruit.com/assets/assets/000/050/058/original/Sensirion_Gas_Sensors_SGP30_Datasheet_EN.pdf
* We used the AMG8833 datasheet to find power requirements. Link:
https://cdn-learn.adafruit.com/assets/assets/000/043/261/original/Grid-EYE_SPECIFICATIONS%28Reference%29.pdf?1498680225
* The HX711 datasheet was helpful for getting current draw information for the scale power budget. Link: https://cdn.sparkfun.com/assets/b/f/5/a/e/hx711F_EN.pdf 
* This HX711 hookup guide was helpful for creating a hardware schematic for the scale and also provided some code to get started with the load sensors and HX711. Link: https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide?_ga=2.233137886.1544447147.1651021976-1626260331.1641614281

## <ins>Power Requirements:</ins>
### Sensor board:
For a sensor board that sends data to the Raspberry Pi every hour (24 times a day), the Feather requires anywhere between 750mAh to 1,125mAh per day. In order to last 122 days (4 months), the required battery size is about 130,000 mAh. On a 2200 mAh battery, the prototyped sensor board will last about 2 days. All the sensors connected to the sensor board run on 3.3V logic.

### Scale:
For a scale that sends data to the Raspberry Pi every hour (24 times a day), the Feather requires anywhere about 700 mAh per day. In order to last 122 days (4 months), the required battery size is about 86,000 mAh. On a 2200 mAh battery, the prototyped scale will last about 3 days. 

## <ins>Photographs:</ins>
* Sensor board:

![Sensor Board](./assets/Sensor%20board.jpg)

* Scale Prototype:

![Scale Prototype]()