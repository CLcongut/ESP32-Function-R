#include <Arduino.h>

// https://docs.geeksman.com/esp32/Arduino/16.esp32-arduino-timer.html

hw_timer_t *tim0 = NULL;
int blinktime;

void Tim0Interrupt()
{
  digitalWrite(2, !digitalRead(2));
  blinktime++;
}

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  tim0 = timerBegin(0, 80, true);
  timerAttachInterrupt(tim0, Tim0Interrupt, true);
  timerAlarmWrite(tim0, 100000, true);
  timerAlarmEnable(tim0);
}

void loop()
{
  if (blinktime >= 20)
  {
    // timerStop(tim0);
    timerAlarmDisable(tim0);
  }
}
