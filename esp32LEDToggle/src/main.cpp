#include "config.h"

#define Sign_Light 2

void task1(void *pt)
{
  pinMode(Sign_Light, OUTPUT);
  for (;;)
  {
    digitalWrite(Sign_Light, !digitalRead(Sign_Light));
    vTaskDelay(500);
  }
}

void setup()
{
  Serial.begin(115200);
  xTaskCreate(task1, "blink18", 1024, NULL, 1, NULL);
  i2cScan();
}

void loop()
{
}