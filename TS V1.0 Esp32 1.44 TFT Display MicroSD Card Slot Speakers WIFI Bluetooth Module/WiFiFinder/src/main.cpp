#include <Arduino.h>
#include "WiFi.h"
#include "Config.h"
#include <Button.h>
#include "startup_music.h"
#include <Speaker.h>
#include <list>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS_PIN, TFT_DC_PIN, TFT_MOSI_PIN, TFT_CLK_PIN, TFT_RST_PIN);

SPEAKER sp = SPEAKER();

#define DEBOUNCE_MS 20
Button BtnA = Button(BUTTON_A_PIN, true, DEBOUNCE_MS);
Button BtnB = Button(BUTTON_B_PIN, true, DEBOUNCE_MS);
Button BtnC = Button(BUTTON_C_PIN, true, DEBOUNCE_MS);

void WifiScan();
void SendList();
uint64_t timer = 0;

struct Wifi
{
	int EncryptionType;
	String Name;

	Wifi(String name, int  encryptionType ) : Name(name), EncryptionType(encryptionType){}
};

std::list<Wifi> listofWiFis = {};

void AddUniqueWifi(Wifi wifi);

void setup()
{
  Serial.begin(115200);

	// for (auto const& i : listofPlayers) {
	//     //std::cout << i.name;
	// 		Serial.println(i.Name);
	// }

	// it = wifilist.begin();
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

  if(timer >= 9000000){
    timer = 0;
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 0);

    WifiScan();
		SendList();
  }

  //  Speaker update
  sp.update();
  // Wait a bit before scanning again
  //    delay(50000);
}
void SendList() {
	for (std::list<Wifi>::iterator it = listofWiFis.begin(); it != listofWiFis.end(); ++it){
		Serial.println(it->Name.c_str());
	}
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

          //listofWiFis.push_back(Wifi(WiFi.SSID(i), WiFi.encryptionType(i)));
					if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
          {
             tft.setTextColor(ST7735_GREEN);
             tft.println(WiFi.SSID(i));
						 AddUniqueWifi(Wifi(WiFi.SSID(i), WiFi.encryptionType(i)));
             sp.tone(3000, 10); //frequency 3000, durtion 100ms
          }
          //else
          //  tft.setTextColor(ST7735_RED);

          // Serial.print(i + 1);
          // Serial.print(": ");
          // Serial.print(WiFi.SSID(i));
          // Serial.print(" (");
          // Serial.print(WiFi.RSSI(i));
          // Serial.print(")");
          // Serial.println(WiFi.encryptionType(i));
        //  delay(10);
      }
  }
}

void AddUniqueWifi(Wifi wifi){
	bool contains = false;
	for (std::list<Wifi>::iterator it = listofWiFis.begin(); it != listofWiFis.end(); ++it){
		//Serial.println(it->Name.c_str());
		if(it->Name == wifi.Name)
		{
			contains = true;
		}
	}
	if(!contains){
		listofWiFis.push_back(wifi);
	}
}
