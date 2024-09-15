/******************************************
 * version:2.1
 * change mode setting
 * add Constructor
 * can use PDM now
 * change name to I2S_93
 * more simple for my projct
 * use esp_log to print info
 * rebuild whole lib
 * remove namespace
 * add some note for function
 */
#include "I2S_93.h"

I2S_93::I2S_93(uint8_t deviceIndex, i2smode_t peripheralActor, i2smode_t transmitMode, i2smode_t modulateMode) : _deviceIndex((i2s_port_t)deviceIndex),
                                                                                                                 _transmitMode(transmitMode),
                                                                                                                 _modulateMode(modulateMode),
                                                                                                                 _intrAlloc(0),
                                                                                                                 _dmaBufCnt(16),
                                                                                                                 _dmaBufLen(64),
                                                                                                                 _useApll(false)
{
  _i2sdvsMode = i2s_mode_t(peripheralActor | transmitMode | modulateMode);
}

void I2S_93::begin(uint32_t sampleRate, uint8_t bitsPerSample)
{
  _sampleRate = sampleRate;
  _bitsPerSample = (i2s_bits_per_sample_t)bitsPerSample;
}

void I2S_93::setFormate(i2schnformate_t channelFormate, i2scommformat_t commonFormate)
{
  _channelFormate = (i2s_channel_fmt_t)channelFormate;
  _commonFormate = (i2s_comm_format_t)commonFormate;
}

void I2S_93::setIntrAllocFlags(uint8_t intrAlloc)
{
  _intrAlloc = intrAlloc;
}

void I2S_93::setDMABuffer(int dmaBufCnt, int dmaBufLen)
{
  _dmaBufCnt = dmaBufCnt;
  _dmaBufLen = dmaBufLen;
}

void I2S_93::install(int bckPin, int wsPin, int dataPin)
{
  i2s_config_t i2s_config = {
      .mode = _i2sdvsMode,
      .sample_rate = _sampleRate,
      .bits_per_sample = _bitsPerSample,
      .channel_format = _channelFormate,
      .communication_format = _commonFormate,
      .intr_alloc_flags = _intrAlloc,
      .dma_buf_count = _dmaBufCnt,
      .dma_buf_len = _dmaBufLen,
      .use_apll = _useApll};

  i2s_pin_config_t pin_config;
  switch (_transmitMode | _modulateMode)
  {
  case RX | PCM:
    pin_config = {
        .bck_io_num = bckPin,
        .ws_io_num = wsPin,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = dataPin};
    break;

  case RX | PDM:
    pin_config = {
        .bck_io_num = I2S_PIN_NO_CHANGE,
        .ws_io_num = bckPin,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = dataPin};
    break;

  case TX | PCM:
    pin_config = {
        .bck_io_num = bckPin,
        .ws_io_num = wsPin,
        .data_out_num = dataPin,
        .data_in_num = I2S_PIN_NO_CHANGE};
    break;

  case TX | PDM:
    pin_config = {
        .bck_io_num = I2S_PIN_NO_CHANGE,
        .ws_io_num = bckPin,
        .data_out_num = dataPin,
        .data_in_num = I2S_PIN_NO_CHANGE};
    break;
  }
  if (ESP_OK != i2s_driver_install(_deviceIndex, &i2s_config, 0, NULL))
  {
    log_e("I2S install failed!");
    return;
  }
  if (ESP_OK != i2s_set_pin(_deviceIndex, &pin_config))
  {
    log_e("I2S set pins failed!");
    return;
  }
  log_i("I2S Successfully installed!\r\n");
}

void I2S_93::install(int bckPin, int dataPin)
{
  I2S_93::install(bckPin, I2S_PIN_NO_CHANGE, dataPin);
}

size_t I2S_93::Read(void *storageAddr, int sampleSize)
{
  size_t recvSize;
  i2s_read(_deviceIndex, storageAddr, sampleSize * _bitsPerSample / 8, &recvSize, portMAX_DELAY);
  return recvSize;
}

size_t I2S_93::Write(void *storageAddr, int sampleSize)
{
  size_t sendSize;
  i2s_write(_deviceIndex, storageAddr, sampleSize * _bitsPerSample / 8, &sendSize, portMAX_DELAY);
  return sendSize;
}

void I2S_93::End()
{
  i2s_driver_uninstall(_deviceIndex);
}