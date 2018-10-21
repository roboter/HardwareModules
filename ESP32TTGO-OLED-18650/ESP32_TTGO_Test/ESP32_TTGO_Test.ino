
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // legacy include: `#include "SSD1306.h"`
#include <A4988.h>
// using a 200-step motor (most common)
#define MOTOR_STEPS 200
#define MICROSTEPS 1
// configure the pins connected


#define LED 16
SSD1306Wire  display(0x3c, 5, 4, GEOMETRY_128_64);

void setup() {
  
  pinMode(LED, OUTPUT);
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setContrast(255);
}
float del = 1;
float i = 1;
int button1 = HIGH;
int button2 = HIGH;
int button3 = HIGH;
bool running = false;

void drawDisplay(int pos) {
  // put your main code here, to run repeatedly:

  display.clear();
  // Print to the screen
  // digitalWrite(D0,HIGH);
  // digitalWrite(D4,HIGH);

  display.drawRect(0, 12, 128, 10);
  display.fillRect(0, 12, pos, 10);

  if (running) {
    display.drawString(0, 20, "stop ");
    display.drawString(0, 0, "a1: " + String((int)i));
  } else {
    display.drawString(0, 0, "b1: " + String((int)pos));
  }
  display.display();
}

void loop() {
 
 
  drawDisplay(100);
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(1000);
 

}
