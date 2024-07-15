#include <Arduino.h>

#define Sign_Light 2
#define UserLED1 18
#define UserLED2 19

void task1(void *pt)
{
  pinMode(UserLED1, OUTPUT);
  for (;;)
  {
    digitalWrite(UserLED1, !digitalRead(UserLED1));
    vTaskDelay(500);
  }
}

void task2(void *pt)
{
  pinMode(UserLED2, OUTPUT);
  for (;;)
  {
    digitalWrite(UserLED2, !digitalRead(UserLED2));
    vTaskDelay(800);
  }
}

void setup()
{
  xTaskCreate(
      task1,
      "blink18",
      1024,
      NULL,
      1,
      NULL);

  xTaskCreate(
      task2,
      "blink19",
      1024,
      NULL,
      1,
      NULL);
}

void loop()
{
}