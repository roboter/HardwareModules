#include <SPI.h>
#include <Wire.h>
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include <A4988.h>
#include <WiFi.h>

// SSID et mot de passe des réseaux à tester - SSID and password of the networks to check
// Ajoutez autant de réseau que désiré - Add as network as desired
String ssids[3] = {"yourSSID1", "yourSSID2", "yourSSID3"};
String passwords[3] = {"pwdSSID1", "pwdSSID2", "pwdSSID3"};

// IP du serveur de test - Test server IP
const char* host = "xxx.xxx.xxx.xxx";
// Port du serveur - Server Port
const int port = 8080;

SSD1306Wire  display(0x3c, 5, 4);

// Initialisation des Objets - Init objects
WiFiClient wifi;
//HTTPClient http;

// Fonction de connexion au réseau WiFi
void setup_wifi(String ssid, String password) {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Il faut convertir la String en char* - need to convert String to char*
  WiFi.begin(ssid.c_str(), password.c_str());
  // Connexion au réseau WiFi - connecting to WiFi network
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    count++;
    delay(500);
    Serial.print(".");
    if ( count > 10 ) {
      return;
    }
  }

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
// Adapted from Adafruit_SSD1306
void drawLines() {
  for (int16_t i = 0; i < display.getWidth(); i += 4) {
    display.drawLine(0, 0, i, display.getHeight() - 1);
    display.display();
    delay(10);
  }
  for (int16_t i = 0; i < display.getHeight(); i += 4) {
    display.drawLine(0, 0, display.getWidth() - 1, i);
    display.display();
    delay(10);
  }
  delay(250);

  display.clear();
  for (int16_t i = 0; i < display.getWidth(); i += 4) {
    display.drawLine(0, display.getHeight() - 1, i, 0);
    display.display();
    delay(10);
  }
  for (int16_t i = display.getHeight() - 1; i >= 0; i -= 4) {
    display.drawLine(0, display.getHeight() - 1, display.getWidth() - 1, i);
    display.display();
    delay(10);
  }
  delay(250);

  display.clear();
  for (int16_t i = display.getWidth() - 1; i >= 0; i -= 4) {
    display.drawLine(display.getWidth() - 1, display.getHeight() - 1, i, 0);
    display.display();
    delay(10);
  }
  for (int16_t i = display.getHeight() - 1; i >= 0; i -= 4) {
    display.drawLine(display.getWidth() - 1, display.getHeight() - 1, 0, i);
    display.display();
    delay(10);
  }
  delay(250);
  display.clear();
  for (int16_t i = 0; i < display.getHeight(); i += 4) {
    display.drawLine(display.getWidth() - 1, 0, 0, i);
    display.display();
    delay(10);
  }
  for (int16_t i = 0; i < display.getWidth(); i += 4) {
    display.drawLine(display.getWidth() - 1, 0, i, display.getHeight() - 1);
    display.display();
    delay(10);
  }
  delay(250);
}
void setup() {
  pinMode(A0, INPUT);  // Le convertisseur A/N A0 sera utilisé pour mesurer la tension de la batterie - Set A0 converter as input to measure the battery tension
  Serial.begin(115200);
  display.init();
  // display.flipScreenVertically();
  //  display.setFont(ArialMT_Plain_10);
  display.setContrast(255);

  //  drawLines();
  //  delay(1000);
  //  display.clear();
  //  display.println("hello world");
  //  // Draw it to the internal screen buffer
  //  display.drawLogBuffer(0, 0);
  //  // Display it on the screen
  //  display.display();
  //  delay(500);
  //  delay(1000);
  //  display.clear();
  //    printBuffer();
  //delay(1000);
  //display.clear();
}

float getLevel() {
  float raw = analogRead(A0);
  int level = map(raw, 140, 227, 0, 100);     // Avec une résistance 1M5 - With a 1M5 resistor
  Serial.print("A0 "); Serial.println(raw);

  if ( level < 0 ) {
    level = 0;
  }
  if ( level > 100 ) {
    level = 100;
  }
  Serial.print("Level: "); Serial.println(level);
  return level;
}

float getVoltage() {
  float raw = analogRead(A0);
  float volt = map(raw, 140, 227, 338, 511);  // Avec une résistance 1M5 - With a 1M5 resistor
  volt = volt / 100;
  Serial.print("A0 "); Serial.println(raw);
  Serial.print("Voltage "); Serial.println(volt);
  return volt;
}

void loop() {
  byte available_networks = WiFi.scanNetworks();
  if ( available_networks > 0 ) {
    for (int network = 0; network < available_networks; network++) {
      delay(1000);
      int level = getLevel();
      long rssi = WiFi.RSSI(network);
      int bars = getBarsSignal(rssi);
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID(network));
      Serial.print("RSSI:");
      Serial.println(rssi);

      display.clear();
      display.setLogBuffer(5, 30);
      //   display.setColor(WHITE);
      // display.setContrast(255);

      //      display.setTextSize(1);
      //      display.setTextColor(WHITE);
      //  display.setCursor(0,0);
      //display.drawString(0, 20, "stop ");
      // Affiche le nom du réseau, la qualité du signal et le niveau de la batteri - display network name, signal Strength and battery level
      int lineHeight = 8;
      display.println("SSID: " + WiFi.SSID(network));
      display.println( "RSSI: " + String((int)rssi));
      display.display();
      delay(200);
      //   display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000011);
      // display.drawString(0,lineHeight*4,"Bat.");
      // display.drawString(0,lineHeight*5,String(level));// display.println("%");
      //      uint8_t buffer[64*16/8];
      //   NanoCanvas canvas(64,16, buffer);
      // Affiche les barres de réception du signal - display signal quality bars
      display.drawLogBuffer(0, 0);
      for (int b = 0; b <= bars; b++) {
        //      canvas.clear();
        //   canvas.fillRect(10, 3, 80, 5, 0xFF);
        display.drawRect(59 + (b * 5), 50 - (b * 5), 3, b * 5);
     //   display.drawRect(10 + (b * 5), 48 - (b * 5), 3, b * 5);
      }

      display.display();
      delay(2000);

      // Vérifie si la connexion au serveur fonctionne - Check if connexion is correct with the server
      for ( int i = 0 ; i < 3 ; i++ ) {
        String _ssid = ssids[i];
        String _pwd = passwords[i];
        String _currentSSID = WiFi.SSID(network);
        if ( _currentSSID == _ssid) {
          checkServerConnexion(_ssid, _pwd);
        }
      }
    }
  } else {
    displayMessage("No Signal !", 1000, 1);
  }
}

void checkServerConnexion(String ssid, String password) {
  Serial.println("Checking server connexion...");
  displayMessage("Checking server connexion...", 250, 1);
  setup_wifi(ssid, password);
  String _status = ssid;
  //http.setTimeout(1000);
  //http.begin(host,port, "/checkconnexion");
  //int httpCode = http.GET();
  //Serial.print("HTTP Code "); Serial.println(httpCode);
  //if (httpCode) {
  //    if (httpCode == 200) {
  //Serial.println("Connexion OK");
  //_status += " OK";
  //displayMessage(_status, 2000,2);
  //} else {
  //      Serial.println("Connexion KO");
  //_status += " KO!";
  //displayMessage(_status, 2000, 2);
  //}
  //} else {
  //    Serial.println("Connexion KO");
  //_status += " KO!";
  //displayMessage(_status, 2000, 2);
  //}
  //Serial.println("closing connection");
  //http.end();
}

void displayMessage(String message, int duration, int Size) {
  display.clear();
  // display.setTextSize(Size);
  //  display.setTextColor(WHITE);
  //  display.setCursor(0,0);
  display.println(message);
  display.display();
  delay(duration);
}

int getBarsSignal(long rssi) {
  // 5. High quality: 90% ~= -55db
  // 4. Good quality: 75% ~= -65db
  // 3. Medium quality: 50% ~= -75db
  // 2. Low quality: 30% ~= -85db
  // 1. Unusable quality: 8% ~= -96db
  // 0. No signal
  int bars;

  if (rssi > -55) {
    bars = 5;
  } else if (rssi < -55 & rssi > -65) {
    bars = 4;
  } else if (rssi < -65 & rssi > -75) {
    bars = 3;
  } else if (rssi < -75 & rssi > -85) {
    bars = 2;
  } else if (rssi < -85 & rssi > -96) {
    bars = 1;
  } else {
    bars = 0;
  }
  return bars;
}
