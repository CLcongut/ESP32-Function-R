#include <Arduino.h>

void setup()
{
  // Serial.begin(115200);
  Serial0.begin(115200);
}

void loop()
{
  Serial0.println("HELLOW");
  delay(1000);
}
