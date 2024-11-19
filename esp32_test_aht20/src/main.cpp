/**************************************************************************
   Tests the getTemperature and getHumidity functions of the aht20 library
 **************************************************************************/
#include <Wire.h>
#include <AHT20.h>
AHT20 aht20;

// #define AHT20_TEST

void setup() {
  Serial.begin(115200);
#ifdef AHT20_TEST
  Serial.println("Humidity AHT20 examples");

  Wire.setPins(4, 16);
  Wire.begin();  // Join I2C bus

  // Check if the AHT20 will acknowledge
  if (aht20.begin() == false) {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    while (1);
  }
  Serial.println("AHT20 acknowledged.");
#endif
  pinMode(4, INPUT);
}

void loop() {
// If a new measurement is available
#ifdef AHT20_TEST
  if (aht20.available() == true) {
    // Get the new temperature and humidity value
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();

    // Print the results
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.print(" C\t");
    Serial.print("Humidity: ");
    Serial.print(humidity, 2);
    Serial.print("% RH");
    Serial.println();
  }
#endif
  // The AHT20 can respond with a reading every ~50ms. However, increased read
  // time can cause the IC to heat around 1.0C above ambient. The datasheet
  // recommends reading every 2 seconds.
  delay(10);
  Serial.print(millis());
  Serial.print("  ");
  // Serial.println(aht20.getTemperature());
  Serial.println(analogRead(4));
}
