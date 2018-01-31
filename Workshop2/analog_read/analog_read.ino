/*
  Analog Read

  This program sets up one of the analog pins to read in voltage from the 
  sample circuit.
  
  modified by 30 Jan 2018
  by Thomas Fuller
 */

// Conversion factor for ADC to Volt
double const ADC_TO_VOLT = 1023.0 / 5.0; 

void setup() {
  // Setup analog pin and initialize serial
  pinMode(A3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Read value from the A3 pin and print it out
  int x = analogRead(A3);
  Serial.print("\nAnalog Value: ");
  Serial.println(x);

  // Convert ADC value to voltage and print it out 
  double voltage = x / ADC_TO_VOLT;
  Serial.print("Estimated Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Wait a second...
  delay(1000);
}
