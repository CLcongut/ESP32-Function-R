#include <Arduino.h>
#include "I2S_93.h"

const int BLOCK_SIZE = 1000;
int16_t samples[BLOCK_SIZE];

I2S_93 mems(0, mems.MASTER, mems.RX, mems.PDM);

void setup()
{
  Serial.begin(115200);

  mems.begin(10000, 16);
  mems.setFormate(mems.RIGHT_LEFT, mems.PCM_SHORT);
  mems.install(27, 26);
}

void loop()
{
  mems.Read(samples, BLOCK_SIZE);

  for (uint32_t i = 0; i < BLOCK_SIZE; i++)
  {
    Serial.printf("%d\n", samples[i]);
  }
}