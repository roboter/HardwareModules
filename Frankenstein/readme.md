#Programming
Same as ESP-01

#device
Model: ESP-12E

#
boot0 - not connected = run mode


Plugging in with boot0 pressed
pressing reset after `Hard resetting via RTS pin...` displayed

JUST RESET While holding boot0 is sufficent to program

# 
LED_BUILTIN - Blue LED on ESP-01 module
13 - LED is on Arduino module

http://www.esp8266learning.com/tm1637-7-segment-display-example.php


#include <TM1637Display.h>

// Module connection pins (Digital Pins)
const int CLK = D6; //Set the CLK pin connection to the display
const int DIO = D5; //Set the DIO pin connection to the display