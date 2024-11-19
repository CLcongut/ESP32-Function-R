#include <Arduino.h>

#define uS_TO_S_FACTOR 1000000 /* 微秒到秒的转换系数 */
#define TIME_TO_SLEEP 5        /* ESP32休眠时间(单位秒) */

void setup()
{
  Serial.begin(115200);
  pinMode(48, OUTPUT);
  pinMode(0, INPUT);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  // esp_sleep_enable_ext0_wakeup(GPIO_NUM_0, 0);
}

void loop()
{
  while (digitalRead(0) == LOW)
  {
    digitalWrite(48, !digitalRead(48));
    delay(100);
  }
  digitalWrite(48, HIGH);
  delay(1000);
  Serial.println("进入休眠模式");
  esp_deep_sleep_start();
  digitalWrite(48, LOW);
  delay(1000);
}