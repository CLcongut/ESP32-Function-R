#include <Arduino.h>

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch Test");
  pinMode(18, OUTPUT);
}

void loop()
{
  digitalWrite(18, LOW);
  Serial.println(touchRead(4)); // GPIO 4
  delay(1000);
  digitalWrite(18, HIGH);
  delay(1000);
}
