/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 *  Arduino IDE 1.6.6
 *  Sketch uses 236,148 bytes (45%) of program storage space. Maximum is 524,288 bytes.
 */

#include <WiFi.h>
#include <Wire.h>

void setup() 
{
  Serial.begin(115200);                   // diagnostic channel
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  //Wire.pins(int sda, int scl), etc
//  Wire.pins(4, 5);                        //on ESP-01.
  Wire.begin();
  StartUp_OLED();                         // Init Oled and fire up!
  Serial.println("OLED Init... End of Setup()");
  /*  I did not write the OLED functions... note that sendStrXY is in reality sendStrYX !!!
   *  Just deal with it: maybe original author had screen in a different orientation plane.
  sendStrXY("Line 0..........", 0, 0);  // a Full line #0 Max lines =7 for 8 total lines
  sendStrXY("Line 1.", 1, 0);
  sendStrXY("Line 2.", 2, 0);
  sendStrXY("Line 3.", 3, 0);
  sendStrXY("Line 4.", 4, 0);
  sendStrXY("Line 5.", 5, 0);
  sendStrXY("Line 6.", 6, 0);
  sendStrXY("Line 7.", 7, 0);
  delay(10000);
  */
}


void loop() 
{
  clear_display();                        // done here to simplify also setXY(0,0);
  Serial.print("Scan start. ");
  sendStrXY(">>> Scanning <<<", 0, 0);
  int n = WiFi.scanNetworks();            // WiFi.scanNetworks will return the number of networks found
  int ln = 0;                             // OLED to print line: 0 - 4
  char *WiFiSSID = "";
  Serial.print("Done: ");
  sendStrXY("-- Open Wifi: --", ln++, 0);    // 16 Character max per line with font set
  
  if (n == 0)
  {
    Serial.println("no networks found");
    sendStrXY("No Nets in Range", ln++, 0);
    delay(2000);
    return;
  } else
  {
    Serial.print(n);
    Serial.println(" networks found");
    // sendStrXY("Scan Listing:   ", ln++, 0);
  
    for (uint8_t i = 1; i <= n; ++i)         // Print SSID and RSSI for each network found
    {
      Serial.print(i);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
    }
  
    for (uint8_t i = 1; i <= n; ++i)
    {
      if (ln % 8 == 0)
      {
          delay(3000);
          clear_display();
          ln = 0;
          sendStrXY("----- more -----", ln++, 0);
      }

      if (WiFi.encryptionType(i) == ENC_TYPE_NONE) {
        strcpy (WiFiSSID, WiFi.SSID(i));
        sendStrXY(WiFiSSID, ln++, 0);
      }
    }
  }
  Serial.println("10 sec. delay until repeat...");
  delay(10000);                             // Wait a while before scanning again
}                                           // loop
