/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
Board : Mapple Mini
Bootloader: Original 
Bootloader: 2.0
CPU: Speed 72
Optimise: Smallest
Port: (Mapple Mini)

Jumpers: Boot0:0 Boot1:1

nO NEED Programming Hit reset

 */
#define LED PA1
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin PB1 as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(20);              // wait for a second
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(20);              // wait for a second  
}
