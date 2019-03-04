#include <Arduino.h>
#include "WiFi.h"
#include "Config.h"
//#include <M5Stack.h>
#include <Button.h>
#include "startup_music.h"
#include <Speaker.h>

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
#define TFT_MOSI 23   // set these to be whatever pins you like!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

SPEAKER sp = SPEAKER();

#define DEBOUNCE_MS 20
Button BtnA = Button(BUTTON_A_PIN, true, DEBOUNCE_MS);
Button BtnB = Button(BUTTON_B_PIN, true, DEBOUNCE_MS);
Button BtnC = Button(BUTTON_C_PIN, true, DEBOUNCE_MS);
void WifiScan();
uint64_t timer = 0;

void setup()
{
    // Setup the button with an internal pull-up
    // pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    // pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    // pinMode(BUTTON_C_PIN, INPUT_PULLUP);
    Serial.begin(115200);

    // Use this initializer if you're using a 1.8" TFT
    tft.initR(INITR_144GREENTAB); // initialize a ST7735S chip, black tab
    //tft.setRotation(1);
    tft.setRotation(3);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // Initialize the M5Stack object
  //  M5.begin();

  sp.setVolume(8);
  sp.playMusic(m5stack_startup_music, 25000);
//  sp.beep();
//  sp.tone(3000, 200);
//  sp.update();
  Serial.println("Setup done");
}

void loop()
{
  //Button update
  BtnA.read();
  BtnB.read();
  BtnC.read();

  if(BtnA.wasPressed())
  {
    //sp.beep();
    tft.println("wasPressed A");
    Serial.println("A");
  }

  if(BtnB.wasPressed())
  {
      sp.tone(3000, 100); //frequency 3000, durtion 200ms
      tft.println("wasPressed B");
      Serial.println("B");
  }

  if(BtnC.wasPressed())
  {
      sp.playMusic(m5stack_startup_music, 25000);
      tft.println("wasPressed C");
      Serial.println("C");
  }

  timer++;

  if(timer>= 9000000){
    timer = 0;
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);

    WifiScan();
  }

  //  Speaker update
  sp.update();
  // Wait a bit before scanning again
  //    delay(50000);
}

void WifiScan(/* arguments */)
 {
  /* code */
  Serial.println("scan start");

// WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i) {
          // Print SSID and RSSI for each network found
    //      tft.println(tft.getRotation() );
          if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
          {
             tft.setTextColor(ST7735_GREEN);
             tft.println(WiFi.SSID(i));
             sp.tone(3000, 10); //frequency 3000, durtion 100ms
             //sp.beep();
          }
          //else
          //  tft.setTextColor(ST7735_RED);

          Serial.print(i + 1);
          Serial.print(": ");
          Serial.print(WiFi.SSID(i));
          Serial.print(" (");
          Serial.print(WiFi.RSSI(i));
          Serial.print(")");
          Serial.println(WiFi.encryptionType(i));
        //  delay(10);
      }
    }
}
