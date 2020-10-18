# Features

 * ESP-WROOM-32 Module (Wifi, Bluetooth, two cores)
 * USB to serial bridge with Silicon Labs CP210X Chip
 (supported by Windows and Linux)
 * Charge Circuit for an 18650 battery (backside of board)
 * OLED display (SSD1306 or compatible) I2C version
 * LED on GPIO16
 * power switch

http://www.areresearch.net/2018/01/how-to-use-ttgo-esp32-module-with-oled.html


Needs Library
https://github.com/ThingPulse/esp8266-oled-ssd1306
and TimeLib

# battery level 
float batteryLevel = map(analogRead(33), 0.0f, 4095.0f, 0, 100);

chip TP5410

# ARDUNIO 
* Board: ESP32 Dev Module

# HARDWARE
LED =  GPIO16[D0]
bootButton = 0

# scematic
https://www.espressif.com/en/products/hardware/esp32-devkitc/resources

# OLED
Unlike on other ESP32 boards with OLEDs, the OLED's I2C SDA and SCL pins are connected as follows:

* SCL - Pin 4
* SDA - Pin 5

It does not require an "enable" signal on GPIO16 as suggested in some programs I found. So comment these out if you see them.

# Pinout
![Pinout](pinout.png)
