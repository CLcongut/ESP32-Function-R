#include <Arduino.h>
#include <driver/i2s.h>

#define SAMPLE_BUFFER_SIZE 2048
#define SAMPLE_RATE 10000
#define I2S_MIC_SERIAL_CLOCK 14
#define I2S_MIC_LEFT_RIGHT_CLOCK 27
#define I2S_MIC_SERIAL_DATA 26

i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    // I2S_COMM_FORMAT_I2S is deprecated, instead of I2S_COMM_FORMAT_STAND_I2S
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 16,
    .dma_buf_len = 64,
    .use_apll = false};

// i2s0 : 32, 33, 25
// i2s1 : 26, 27, 14

i2s_pin_config_t i2s_mic_pins = {
    .bck_io_num = 26,
    .ws_io_num = 27,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = 14};

void setup()
{
  Serial.begin(115200);
  Serial.println("check!");
  pinMode(2, OUTPUT);
  
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &i2s_mic_pins);
}

int32_t raw_samples[SAMPLE_BUFFER_SIZE];
// int32_t cook_samples[SAMPLE_BUFFER_SIZE];

void loop()
{
  digitalWrite(2, HIGH);
  size_t bytes_read = 0;
  i2s_read(I2S_NUM_0, raw_samples, sizeof(int32_t) * SAMPLE_BUFFER_SIZE, &bytes_read, portMAX_DELAY);
  int samples_read = bytes_read / sizeof(int32_t);
  for (int i = 0; i < samples_read; i++)
  {
    Serial.printf("%d\n", raw_samples[i] >> 8);
    // Serial.println();
  }
  digitalWrite(2, LOW);
  // Serial.println(bytes_read);
}
