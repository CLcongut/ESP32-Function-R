#include <Arduino.h>
#include <SPI.h>
#include "SdFat.h"

static SdFs sd;
static FsFile root;
static FsFile file;

uint8_t *data_invt;

void setup()
{
  Serial.begin(115200);
  if (!sd.begin(SdSpiConfig(10, DEDICATED_SPI, 18e6)))
  {
    log_e("Card Mount Failed");
  }
  root.open("/", O_WRITE);
  file.open("speedtest.txt", O_WRITE | O_CREAT);
  file.close();
  root.close();

  data_invt = (uint8_t *)calloc(20000, sizeof(uint8_t));
  memset(data_invt, 0xfe, 20000);
}

void loop()
{
  log_e("storage Start");
  root.open("/", O_WRITE);
  file.open("speedtest.txt", O_WRITE | O_APPEND);
  file.write(data_invt, 20000);
  file.close();
  root.close();
  log_e("storage End");
}