#include <Arduino.h>
#include <WIFI.h>

#define wifi_SSID "副WLW"       // WIFI名字，不可中文
#define wifi_PSWD "WLW11223344" // WIFI密码，不可中文，最好 8 位

#define sign_LED 2

TaskHandle_t Task1;
TaskHandle_t Task2;

void Task1code(void *pvParameters);
void Task2code(void *pvParameters);

WiFiUDP udp;
IPAddress remote_IP(192, 168, 1, 111);
// IPAddress remote_IP(192, 168, 4, 2);

uint32_t remoteUdpPort = 6060;

uint16_t *pintger;
String pstr;

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
  for (int i = 0; i <= 65535; i++)
  {
    // pintger[i] = random(65535);
    pintger[i] = i;
    // pintger[i] = 255;
  }

  xTaskCreatePinnedToCore(
      Task1code,
      "Task1",
      10000,
      NULL,
      1,
      &Task1,
      0);
  delay(100);

  xTaskCreatePinnedToCore(
      Task2code,
      "Task2",
      10000,
      NULL,
      1,
      &Task2,
      1);
  delay(100);
}

void Task1code(void *pvParameters)
{
  for (;;)
  {
    vTaskDelay(100);
    // for (int i = 0; i <= 9999; i++)
    // {
    //   Serial.println(pintger[i]);
    // }
  }
}

void Task2code(void *pvParameters)
{
  // for (int i = 0; i <= 9999; i++)
  // {
  //   pstr += pintger[i];
  // }
  // free(pintger);

  while (touchRead(4) > 20)
    ;

  digitalWrite(sign_LED, HIGH);

  udp.beginPacket(remote_IP, remoteUdpPort);
  // udp.println(pstr);
  for (int i = 0; i <= 65535; i++)
  {
    udp.printf("%x", pintger[i]);
  }

  Serial.println(millis());

  udp.endPacket();

  Serial.println(millis());

  digitalWrite(sign_LED, LOW);
  for (;;)
  {
    if (touchRead(32) < 20)
    {
      // esp_restart();
      return;
    }
  }
}

void loop()
{
}
