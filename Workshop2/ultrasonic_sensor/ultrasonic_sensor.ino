0/*
  Ultrasonic Sensor

  This program interfaces with the ultrasonic sensor in order to read 
  and display distance information.

  Code used from https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380

  modified 30 Jan 2018
  by Thomas Fuller
 */

const int trigPin = 11; 
const int echoPin = 12;

float duration, distance;

void setup() {
  // Set up trig and echo pins, and then start Serial 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600); 
}

void loop() { 
  // Trigger the ultrasonic sensor to send out a pulse
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  // Read incoming pulse to the sensor
  duration = pulseIn(echoPin, HIGH);

  // Convert duration to distance and display the result
  distance = (duration*.0343)/2;
  Serial.print("Distance: "); 
  Serial.println(distance); 
  delay(100); 
}
