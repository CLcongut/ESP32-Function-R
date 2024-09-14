/**
 * ESP32 I2S Noise Level Example.
 *
 * This example calculates a mean noise level.
 * This example is Public Domain.
 *
 * @author maspetsberger
 */
#include <Arduino.h>
#include <driver/i2s.h>
#include "I2S_93.h"

const int BLOCK_SIZE = 1024;
int16_t samples[BLOCK_SIZE];

void setup()
{
  Serial.begin(115200);
  Serial.println("Configuring I2S...");
  esp_err_t err;

  // The I2S config as per the example
  const i2s_config_t i2s_config = {
      .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM), // Receive, not transfer
      .sample_rate = 16000,                                             // 16KHz
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,                     // could only get it to work with 32bits
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                     // although the SEL config should be left, it seems to transmit on right
      .communication_format = I2S_COMM_FORMAT_STAND_PCM_SHORT,
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // Interrupt level 1
      .dma_buf_count = 8,                       // number of buffers
      .dma_buf_len = BLOCK_SIZE                 // samples per buffer
  };

  // The pin config as per the setup
  const i2s_pin_config_t pin_config = {
      .bck_io_num = -1,   // BCKL
      .ws_io_num = 27,    // LRCL
      .data_out_num = -1, // not used (only for speakers)
      .data_in_num = 26   // DOUT
  };

  // Configuring the I2S driver and pins.
  // This function must be called before any I2S driver read/write operations.
  err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  if (err != ESP_OK)
  {
    Serial.printf("Failed installing driver: %d\n", err);
    while (true)
      ;
  }
  err = i2s_set_pin(I2S_PORT, &pin_config);
  if (err != ESP_OK)
  {
    Serial.printf("Failed setting pin: %d\n", err);
    while (true)
      ;
  }
  Serial.println("I2S driver installed.");
}

void loop()
{

  // Read multiple samples at once and calculate the sound pressure

  size_t num_bytes_read;
  i2s_read(I2S_PORT,
           samples,
           sizeof(int16_t) * BLOCK_SIZE,
           &num_bytes_read, // the doc says bytes, but its elements.
           portMAX_DELAY);  // no timeout

  // int samples_read = num_bytes_read / 8;
  // if (samples_read > 0)
  // {

  //   float mean = 0;
  //   for (int i = 0; i < samples_read; ++i)
  //   {
  //     mean += samples[i];
  //   }
  //   Serial.println(mean);
  // }
  // int16_t *usprt = (int16_t *)samples;
  for (uint32_t i = 0; i < BLOCK_SIZE; i++)
  {
    Serial.printf("%d\n", samples[i]);
  }
}

// actually we would need to call `i2s_driver_uninstall(I2S_PORT)` upon exit.