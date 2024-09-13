#include <Arduino.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht20_1;

void setup()
{
    Serial.begin(9600);
    aht20_1.begin();
}

void loop()
{
    sensors_event_t humidity, temp;
    aht20_1.getEvent(&humidity, &temp); // populate temp and humidity objects with fresh data
    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.println(" degrees C");
    Serial.print("Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println("% rH");
    delay(1000);
}