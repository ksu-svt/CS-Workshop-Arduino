// which analog pin to connect
#define THERMISTORPIN A0

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
  Serial.println(res);
  float steinhart;
  steinhart = res / THERMISTORNOMINAL;              // (R/Ro)
  steinhart = log(steinhart);                       // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                      // Invert
  steinhart -= 273.15;                              // convert to C
  return steinhart;
}
 
void setup(void) {
  Serial.begin(9600);
  analogReference(EXTERNAL);
}
 
void loop(void) {
  float average = sampleAverage();
  Serial.print("Average analog reading "); 
  Serial.println(average);
 
  // convert the value to resistance
  average = 1023 / average - 1;
  average = SERIESRESISTOR / average;
  Serial.print("Thermistor resistance "); 
  Serial.println(average);

  float temp = resToTemp(average);
  Serial.print("Temperature "); 
  Serial.print(temp);
  Serial.println(" *C");
 
  delay(1000);
}
