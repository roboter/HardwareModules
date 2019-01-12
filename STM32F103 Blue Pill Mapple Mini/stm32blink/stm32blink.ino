/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
Board : Mapple Mini
Bootloader: Original
CPU: Speed 72
Optimise: Smallest
Port: (Mapple Mini)

When Programming Hit reset (Yes every time)

 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin PB1 as an output.
  pinMode(PC13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PC13, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(20);              // wait for a second
  digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(20);              // wait for a second
  //digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
 // delay(1000);              // wait for a second
}
