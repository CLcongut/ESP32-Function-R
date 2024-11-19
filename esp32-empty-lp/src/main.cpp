#include <Arduino.h>
#define limit 50 // 设置阈值
const int led = 2;

void Touch_callback() // 触摸回调函数
{
  // 为空，只用来唤醒睡眠
}

void task1(void *pvParameters)
{
  for (;;) {
    digitalWrite(led, !digitalRead(led));
    vTaskDelay(200);
  }
}

void task2(void *pvParameters)
{
  for (;;) {
    digitalWrite(led, !digitalRead(led));
    vTaskDelay(500);
  }
}

void setup()
{
  pinMode(led, OUTPUT);
  // touchAttachInterrupt(T0, Touch_callback, limit);
  // esp_sleep_enable_touchpad_wakeup(); // 设置触摸唤醒
  xTaskCreate(task1, "task1", 1024, NULL, 1, NULL);
  // xTaskCreate(task2, "task2", 1024, NULL, 1, NULL);
  xTaskCreatePinnedToCore(task2, "task2", 1024, NULL, 1, NULL, 1);
}

void loop()
{
  // for (char i = 0; i < 10; i++)
  // {
  //   digitalWrite(led, HIGH);
  //   delay(250);
  //   digitalWrite(led, LOW);
  //   delay(250);
  // }
  // esp_deep_sleep_start(); // 进入睡眠模式
  vTaskDelete(NULL);
}
