#include <Arduino.h>
#include <WIFI.h>

#define wifi_SSID "CCongut"  // WIFI名字，不可中文
#define wifi_PSWD "88888888" // WIFI密码，不可中文，最好 8 位

#define sign_LED 2

WiFiUDP udp;
IPAddress remote_IP(192, 168, 31, 199);
// IPAddress remote_IP(192, 168, 4, 2);

uint32_t remoteUdpPort = 6060;

uint16_t *pintger;
String pstr;

bool checkdone = false;

void setup()
{
  pinMode(sign_LED, OUTPUT);
  digitalWrite(sign_LED, LOW);
  Serial.begin(115200);

  // WiFi.softAP("esp32_udp_server");
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false); // 关闭STA模式下wifi休眠，提高响应速度
  WiFi.begin(wifi_SSID, wifi_PSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
  }
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());

  pintger = (uint16_t *)calloc(10000, sizeof(uint16_t));

  for (int i = 0; i < 10000; i++)
  {
    // pintger[i] = random(65535);
    pintger[i] = i;
    // pintger[i] = 255;
  }

  // for (int i = 0; i <= 9999; i++)
  // {
  //   pstr += pintger[i];
  // }
  // free(pintger);
}

void loop()
{
  digitalWrite(sign_LED, HIGH);

  if (touchRead(32) < 20)
  {
    udp.beginPacket(remote_IP, remoteUdpPort);

    // Serial.println(millis());

    for (int i = 0; i < 10000; i++)
    {
      // udp.printf("%x", pintger[i]);
      // udp.write((uint8_t)(pintger[i] >> 8));
      // udp.write((uint8_t)(pintger[i] >> 0));
      udp.write(0xFF);
      udp.write(0xEA);
      udp.write(0x81);
      udp.write(0x00);
      udp.write(0x0A);
      udp.write(0x00);
      udp.write(0x28);
      udp.write(0x49);
    }

    udp.endPacket();

    // Serial.println(millis());

    digitalWrite(sign_LED, LOW);
  }

  // while (touchRead(4) > 20)
  //   ;
  // Serial.println("restart!");
  // return;
}
