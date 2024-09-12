#include <Arduino.h>
/************************************************
 * 首先设置 SdFatConfig.h
 * 改为 UTF-8编码
 * 237行改为:
 * #define USE_UTF8_LONG_NAMES 1
 *
 * GPIO12为strapping引脚，启动时需要低电平
 * 到手时将R21电阻焊下来
 */
#include <SPI.h>
#include "SdFat.h"
SdFs sd;

SPIClass hspi(HSPI);

FsFile root;
FsFile file;

void setup()
{
    Serial.begin(115200);
    Serial.println("ok serial!");
    hspi.begin(14, 26, 13, 15);
    if (!sd.begin(SdSpiConfig(15, DEDICATED_SPI, 18e6, &hspi)))
    {
        Serial.println("error");
        // return;
    }

    auto fstype = sd.fatType();
    switch (fstype)
    {
    case FAT_TYPE_EXFAT:
        Serial.println("ExFat");
        break;
    case FAT_TYPE_FAT12:
        Serial.println("Fat12");
        break;
    case FAT_TYPE_FAT16:
        Serial.println("Fat16");
        break;
    case FAT_TYPE_FAT32:
        Serial.println("Fat32");
        break;
    default:
        Serial.println("error");
        break;
    }

    auto size = sd.card()->sectorCount() * 512e-9;
    Serial.printf("it's %f GB\r\n", size);

    // pinMode(2, OUTPUT);
    // esp_sleep_enable_timer_wakeup(5e6);

    if (!root.open("/", O_RDWR))
    {
        Serial.println("open / error");
    }
    if (!file.open("testtext.txt", O_CREAT | O_WRITE))
    {
        Serial.println("error");
    }
    auto count = file.write("text so long and 中文测试");
    file.sync();
    file.close();
    // root.close();
    // root.open("/", O_READ);
    char buf[32];
    memset(buf, 0, 32);
    file.open("testtext.txt", O_READ);
    file.read(buf, 32);
    Serial.println(buf);
    file.close();
    root.close();

    // root.open("/", O_WRITE);
    // file.open("testtext.txt", O_WRITE | O_APPEND);
}

void loop()
{
    // for (uint32_t i = 0; i < 3; i++)
    // {
    //     digitalWrite(2, HIGH);
    //     delay(1e3);
    //     digitalWrite(2, LOW);
    //     delay(1e3);
    // }
    // esp_deep_sleep_start();
    // file.write("lalalalalalalalala");
    // file.sync();
}
