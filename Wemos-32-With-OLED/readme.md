ESP32 Chip ID = 61A4972DE6B4


This ESP32 board requires the SSD1306 libraries to communicate with the OLED display, so make sure to include: #include "SSD1306.h" // alias for #include "SSD1306Wire.h"

On this board the I2C communication pins to the OLED display are pin5 (SDA) and pin4 (SCL), so make sure to change the pins in the initialization: SSD1306 display(0x3c, 5, 4);
