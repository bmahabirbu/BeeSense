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
| 2 | Adalogger | Adafruit | $17.98 |
| 3 | Temperature Humidity Sensor | Adafruit | $4.50 |
| 4 | Air Quality Sensor | Adafruit | $35.00 |
| 5 | Analogue Microphone | Adafruit | $7.98 |
| 6 | IR Camera | Adafruit | $44.95 |
| 7 | SD Card | MicroCenter | $3.99 |
| 8 | Stemma Cables (x4) | Adafruit | $3.80 |
| 9 | Female Headers | Adafruit | $0.95 |
| 10 | 2200mAh LiPo Battery | Adafruit | $9.95 |
| 11 | CR1220 Coin Cell Battery | Adafruit | $0.95 |
| 12 | Sensor Board Case  | Adafruit | $7.95 |
| 13 | Spring Antenna | Adafruit | $0.95 |
| Scale (x1) |
| 14 | LoRa Feather 900MHz | Adafruit | $34.99 |
| 15 | Adalogger | Adafruit | $17.98 |
| 16 | Load Cell (x4) | SparkFun | $15.80 |
| 17 | Load Cell Amplifier | SparkFun | $9.95 |
| 18 | Combinator Board | SparkFun | $1.95 |
| 19 | SD Card | MicroCenter | $3.99 |
| 20 | 2200mAh LiPo Battery | Adafruit | $9.95 |
| 21 | CR1220 Coin Cell Battery | Adafruit | $0.95 |
| 22 | Spring Antenna | Adafruit | $0.95 |
| LoRa Gateway |
| 23 | Raspberry Pi 3B+ | Adafruit | $35.00 |
| 24 | Raspberry Pi LoRa Hat | Adafruit | $32.50 |
| 25 | Raspberry Pi 3B+ Case  | Adafruit | $7.95 |
| 26 | SD Card | MicroCenter | $3.99 |
| 27 | Spring Antenna | Adafruit | $0.95 |
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

![Scale Prototype 1](./assets/Scale%20Prototype%201.jpg)

![Scale Prototype 2](./assets/Scale%20Prototype%202.jpg)

* Beebox with hardware inside:

![Beebox & Scale](./assets/Beebox%2BScale.jpg)

This is the scale underneath the beebox. We are planning to attach the load cells directly to the bottom of the box, but this was the initial setup. 

![Beebox & Sensor](./assets/Beebox%2BSensor.jpg)

This is the top of the beebox, without the lid. The sensor board requires about 4 inches of space between the top of the box (or the hive frames) and the lid. 

## <ins>Hardware Setup:</ins>
Feather hardware setup
1. Connect all sensors using STEMMA cables
    * Solder microphone following adafruit [directions](https://learn.adafruit.com/adafruit-agc-electret-microphone-amplifier-max9814/)

Weight scale hardware setup
1. 3D print half load cell brackets x4
2. Mount brackets with load sensors inside onto a piece of wood that is large enough to accommodate a beebox of the users choosing. You can alternatively attach the load sensors directly to the bottom of a beebox. 
3. Connect all wires to the HX711 load cell amplifier
    * Follow diagram above
4. Connect wires from amp to Feather


Raspberry Pi hardware setup
1. Install LoRa bonnet onto Pi by plugging it in to the 40 pin GPIO
2. Plug USB drive into USB port
