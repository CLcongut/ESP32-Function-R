#include <Arduino.h>
#include <WIFI.h>

#define wifi_SSID "副WLW"       // WIFI名字，不可中文
#define wifi_PSWD "WLW11223344" // WIFI密码，不可中文，最好 8 位

#define sign_LED 2

WiFiUDP udp;
IPAddress remote_IP(192, 168, 1, 111);
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

  for (int i = 0; i <= 9999; i++)
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

  while (touchRead(4) > 20)
    ;

  udp.beginPacket(remote_IP, remoteUdpPort);

  for (int i = 0; i <= 9999; i++)
  {
    // udp.printf("%x", pintger[i]);
    udp.write((uint8_t)(pintger[i] >> 8));
    udp.write((uint8_t)(pintger[i] >> 0));
  }

  Serial.println(millis());

  udp.endPacket();

  Serial.println(millis());

  digitalWrite(sign_LED, LOW);
  while (touchRead(32) > 20)
    ;
  Serial.println("restart!");
  return;
}
