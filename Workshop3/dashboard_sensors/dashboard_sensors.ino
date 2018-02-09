// which analog pins to connect
#define THERMISTORPIN A0
#define SOLARPIN A3

// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000      

// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   

// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5

// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950

// the value of the 'other' resistor
#define SERIESRESISTOR 10000

void setup() {
  Serial.begin(9600);
  pinMode(THERMISTORPIN, INPUT);
  pinMode(SOLARPIN, INPUT);
  analogReference(EXTERNAL);
}

float readSolarPanel() {
  // Conversion factor for ADC to Volt
  double const ADC_TO_VOLT = 1023.0 / 5.0; 
  
  // Read value from the A3 pin and print it out
  int x = analogRead(SOLARPIN);

  // Convert ADC value to voltage and print it out 
  float voltage = x / ADC_TO_VOLT;
  return voltage;
}

/**
 * Samples resistance from the Thermistor.
 */
float sampleAverage() {
  const int NUM_SAMPLES = 5;
  float sum = 0;
  // take N samples in a row, with a slight delay
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sum += analogRead(THERMISTORPIN);
    delay(10);
  }
  return sum / NUM_SAMPLES;
}

/**
 * Converts resistance to temperature in Celcius.
 */
float resToTemp(float res) {
  float steinhart;
  steinhart = res / THERMISTORNOMINAL;              // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // convert to C
  return steinhart;
}

float readThermistor() {
  float average = sampleAverage();
 
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;

  float temp = resToTemp(average);
  return temp;
}

void sendData(float volt, float temp) {
  Serial.print("{");
  Serial.print("\"voltage\":");
  Serial.print(volt);
  Serial.print(",");
  Serial.print("\"temp\":");
  Serial.print(temp);
  Serial.println("}");
}

void loop() {
  float volt = readSolarPanel();
  float temp = readThermistor();
  sendData(volt,temp);
  delay(1000);
}
