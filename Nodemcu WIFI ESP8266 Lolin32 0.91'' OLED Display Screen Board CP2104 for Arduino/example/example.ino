#include <Wire.h>
#include "OLED.h"
//0.91s OLED connection:
//SDA -- D4
//SCL -- D5
//RST -- D2
OLED display(2, 14);
void setup() {
pinMode(D2, OUTPUT);
digitalWrite(D2, LOW); // turn D2 low to reset OLED
delay(50);
digitalWrite(D2, HIGH); // while OLED is running, must set D2 in high
Serial.begin(115200);
Serial.println("OLED test!");
// Initialize display
display.begin();
// Test message
display.print("Hello ");
delay(3*1000);
// Test long message
display.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
delay(3*1000);
// Test display clear
display.clear();
delay(3*1000);
// Test message postioning
display.print("TOP-LEFT");
display.print("4th row", 4);
display.print("RIGHT-BOTTOM", 7, 4);
delay(3*1000);
// Test display OFF
display.off();
display.print("3rd row", 3, 8);
delay(3*1000);
// Test display ON
display.on();
delay(3*1000);
}
int r = 0, c = 0;
void loop() {
r = r % 4;
c = micros() % 6;
if (r == 0) display.clear();
display.print("Hello ", r++, c++);
delay(500);
}
