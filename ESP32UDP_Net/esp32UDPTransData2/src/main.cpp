#include <Arduino.h>
#include <WIFI.h>

#define sign_LED 2

TaskHandle_t Task1;
TaskHandle_t Task2;

void Task1code(void *pvParameters);
void Task2code(void *pvParameters);

void setup()
{
  pinMode(sign_LED, OUTPUT);
  digitalWrite(sign_LED, LOW);

  while (touchRead(4) > 20)
    ;

  xTaskCreatePinnedToCore(
      Task1code,
      "Task1",
      10000,
      NULL,
      1,
      &Task1,
      0);
  delay(100);

  xTaskCreatePinnedToCore(
      Task2code,
      "Task2",
      10000,
      NULL,
      1,
      &Task2,
      1);
  delay(100);
}

void Task1code(void *pvParameters)
{
  digitalWrite(sign_LED, HIGH);
  for (;;)
  {
    delay(1);
  }
}

void Task2code(void *pvParameters)
{
  for (;;)
  {
  }
}

void loop()
{
}
