### TTGO TS V1.0 - ESP32 WiFi BLE + 1.44" TFT LCD + MicroSD Card Slot + Speaker + Battery charger
https://github.com/LilyGO/TTGO-TS-V1.2

# USB Drivers
https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers

# Video
https://www.youtube.com/watch?v=s12XuR7BJkw

# MPU9250 - a 3-axis gyroscope as well as a 3-axis 
v1.0 don't have it


Button Demo - Works
TTGOESP32 - Works
test2 - Works DISPLAY + Music

```
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS 16
#define TFT_RST 9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to -1!
#define TFT_DC 17

#define TFT_SCLK 5   // set these to be whatever pins you like!
#define TFT_MOSI 23   // set these to be whatever pins you like!//sds
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#define TFT_BL      27  // Dispaly backlight control pin

#define BUTTON_1    35
#define BUTTON_2    34
#define BUTTON_3    39

// BEEP PIN
#define SPEAKER_PIN 25
#define TONE_PIN_CHANNEL 0


#define LED_BUILTIN 22
```

Audio = io25 NS4148


https://github.com/LilyGO/TTGO-TS-V1.0
https://github.com/LilyGO/TTGO-TS-V1.2
https://github.com/Xinyuan-LilyGO/TTGO-T4-T10-TestCode


https://github.com/LilyGO/TTGO-TS


ESP32_1.44 - Works
OLED_1.8_inch_tft- Works
 	TEST_speaker - No Sound