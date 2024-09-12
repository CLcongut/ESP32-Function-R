#ifndef __DAC8562_H__
#define __DAC8562_H__

#include "Arduino.h"

#define CMD_SETA_UPDATEA 0x18    // A通道命令+16位A路数据
#define CMD_SETB_UPDATEB 0x19    // B通道命令+16位B路数据
#define CMD_UPDATE_ALL_DACS 0x0F // 更新两路寄存器命令，后16位只需时钟即可

#define CMD_GAIN 0x02          // 内部放大倍数命令
#define DATA_GAIN_B2_A2 0x0000 // B路2倍，A路1倍
#define DATA_GAIN_B2_A1 0x0001 // B路1倍，A路2倍
#define DATA_GAIN_B1_A2 0x0002 // B路2倍，A路2倍
#define DATA_GAIN_B1_A1 0x0003 // B路1倍，A路1倍

#define CMD_PWR_UP_A_B 0x20    // 命令：上电A、B路
#define DATA_PWR_UP_A_B 0x0003 // 数据：Power up DAC-A and DAC-B  data

#define CMD_RESET_ALL_REG 0x28    // 命令：所有寄存器复位、清空寄存器
#define DATA_RESET_ALL_REG 0x0001 // 数据：所有寄存器复位、清空寄存器

#define CMD_LDAC_DIS 0x30    // LDAC脚功能命令
#define DATA_LDAC_DIS 0x0003 // LDAC脚不起作用

#define CMD_INTERNAL_REF_DIS 0x38    // 命令：Disable internal reference and reset DACs to gain = 1
#define DATA_INTERNAL_REF_DIS 0x0000 // 数据：Disable internal reference and reset DACs to gain = 1
#define CMD_INTERNAL_REF_EN 0x38     // 命令：Enable Internal Reference & reset DACs to gain = 2
#define DATA_INTERNAL_REF_EN 0x0001  // 数据：Enable Internal Reference & reset DACs to gain = 2

class DAC8562
{
private:
    uint8_t _cs_pin;
    float _vref;
    float _re_val;

public:
    DAC8562(uint8_t cs_pin);
    DAC8562(uint8_t cs_pin, float vref);

    void begin();
    void initialize();
    void DAC_WR_REG(uint8_t cmd_byte, uint16_t data_byte);
    void outPutValue(uint8_t cmd_byte, uint16_t input);
    void writeValue(uint8_t cmd_byte, uint8_t mid, uint8_t last);
    void writeVoltage(float input);
    void writeA(float input);
    void writeB(float input);
    void volt_revision(float revision_value);
    uint16_t Voltage_Convert(float voltage);
};

#endif