#include "config.h"

#define Sign_Light 2

void task1(void *pt) {
  for (;;) {
    digitalWrite(Sign_Light, !digitalRead(Sign_Light));
    vTaskDelay(500);
  }
}

void setup() {
  Serial.begin(115200);
  // xTaskCreate(task1, "blink18", 1024, NULL, 1, NULL);
  // i2cScan();
  pinMode(Sign_Light, OUTPUT);
  // pinMode(15, INPUT);
}

void loop() {
  // Serial.println(touchRead(15));
  // if (touchRead(15) < 100) {
  //   digitalWrite(Sign_Light, HIGH);
  // } else {
  //   digitalWrite(Sign_Light, LOW);
  // }
  // if (digitalRead(15) == HIGH) {
  //   digitalWrite(Sign_Light, HIGH);
  // } else {
  //   digitalWrite(Sign_Light, LOW);
  // }
  Serial.println(analogRead(35));
  delay(10);
}