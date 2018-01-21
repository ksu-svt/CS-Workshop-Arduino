/*
 Hello World

 Sends 'Hello World!' over serial to the connected computer.

 created 20 January 2018
 by Thomas Fuller
 */
void setup() {
  // Open the serial port at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // Print "Hello World!" to the Serial Monitor
  Serial.println("Hello World!");

  // Delay 5 seconds before the next reading:
  delay(5000);
}
