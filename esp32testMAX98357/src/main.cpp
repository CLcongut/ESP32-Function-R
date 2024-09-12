#include <Arduino.h>
#include "myI2S.h"

#define sample_buffer_size 4000
int32_t *soundata;
static TaskHandle_t audioTask = NULL;

#if 0
void inmp441_Task(void *param)
{
  myI2S microp;
  microp.begin(0);
  microp.SetChannelFormat(ONLY_RIGHT);
  microp.SetInputMode(16, 17, 5);
  for (;;)
  {
    microp.Read(soundata, sample_buffer_size);
    for (uint32_t i = 0; i < sample_buffer_size; i++)
    {
      // Serial.printf("%d\n", soundata[i] >> 8);
      soundata[i] *= 2;
    }

    xTaskNotifyGive(audioTask);
    // vTaskDelay(10);
  }
}
void max98357_Task(void *param)
{
  myI2S audio;
  audio.begin(1);
  audio.SetChannelFormat(ONLY_RIGHT);
  audio.SetOutputMode(13, 12, 14);
  for (;;)
  {
    if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY))
    {
      audio.Write(soundata, sample_buffer_size);
    }
    // vTaskDelay(10);
  }
}
#endif
#if 1

void Duplex_Task(void *param)
{
  myI2S duplex;
  duplex.begin(0);
  duplex.SetChannelFormat(ONLY_RIGHT);
  duplex.SetInOutputMode(13, 12, 5, 14);
  for (;;)
  {
    duplex.Read(soundata, sample_buffer_size);
    for (uint32_t i = 0; i < sample_buffer_size; i++)
    {
      soundata[i] *= 3;
    }
    duplex.Write(soundata, sample_buffer_size);
  }
}

#endif

void setup()
{
  Serial.begin(115200);

  soundata = (int32_t *)calloc(sample_buffer_size, sizeof(int32_t));
#if 0
  xTaskCreate(inmp441_Task, "inmp441_Task", 4096, NULL, 5, NULL);
  xTaskCreate(max98357_Task, "max98357_Task", 4096, NULL, 5, &audioTask);
#endif
#if 1
  xTaskCreate(Duplex_Task, "Duplex_Task", 4096, NULL, 5, NULL);
#endif
}

void loop()
{
}
