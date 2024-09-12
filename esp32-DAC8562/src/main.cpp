#include <Arduino.h>
#include <DAC8562.h>

// This power is for referencing
// In case you do not have a pefect 5 volt power supply.

#define CS_PIN 5

float volt_h = 10;
float volt_l = -10;
float volt_f = 0.1;

DAC8562 dac = DAC8562(CS_PIN);

void setup()
{
  Serial.begin(115200);
  dac.begin();
}

void loop()
{
  String u_temp = "";
  uint8_t i = Serial.available(); // 返回目前串口接收区内的已经接受的数据量
  if (i != 0)
  {
    while (i--)
    {
      u_temp += char(Serial.read()); // 读取一个数据并且将它从缓存区删除
    }

    // float volt_val = u_temp.toFloat();
    // dac.volt_revision(volt_val);
    // Serial.println("revision!");
    static uint8_t volt_val_p = 0;
    if (u_temp.indexOf("volth") != -1)
    {
      volt_val_p = 1;
      Serial.println("change to volt_h");
    }
    else if (u_temp.indexOf("voltl") != -1)
    {
      volt_val_p = 2;
      Serial.println("change to volt_l");
    }
    else if (u_temp.indexOf("voltf") != -1)
    {
      volt_val_p = 3;
      Serial.println("change to volt_f");
    }
    else
    {
      switch (volt_val_p)
      {
      case 1:
        volt_h = u_temp.toFloat();
        Serial.printf("receive :");
        Serial.println(volt_h);
        break;
      case 2:
        volt_l = u_temp.toFloat();
        Serial.printf("receive :");
        Serial.println(volt_l);
        break;
      case 3:
        volt_f = u_temp.toFloat();
        Serial.printf("receive :");
        Serial.println(volt_f);
        break;
      default:
        Serial.println("no setting");
        break;
      }
    }
  }
  // Use these functions to update two channels of the DAC

  // dac.writeB(+50);
  randomSeed(millis());
  for (float val = volt_l; val <= volt_h; val += volt_f)
  {
    dac.writeA(sin(val) * 2 + random(5));
  }
  for (float val = volt_h; val >= volt_l; val -= volt_f)
  {
    dac.writeA(sin(val) * 2 + random(5));
  }
}