#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// 接收端的MAC地址
uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0xA7,0x45,0x2C};

// 发送结构体类型
typedef struct struct_message
{
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// 创建一个结构体变量
struct_message myData;
esp_now_peer_info_t peerInfo;

// 回调函数,函数将在发送消息时执行。此函数告诉我们信息是否成功发送;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  // 初始化串口波特率
  Serial.begin(115200);

  // 设置WIFI模式为STA模式，即无线终端
  WiFi.mode(WIFI_STA);

  //  初始化ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // 注册回调函数
  esp_now_register_send_cb(OnDataSent);

  // 注册通信频道
  // esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;     // 通道
  peerInfo.encrypt = false; // 是否加密为False

  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop()
{
  // 设置要发送的值
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = random(1, 20);
  myData.c = 1.2;
  myData.d = false;

  // 发送信息到指定ESP32上
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));

  // 判断是否发送成功
  if (result == ESP_OK)
  {
    Serial.println("Sent with success");
  }
  else
  {
    Serial.println("Error sending the data");
  }
  delay(2000);
}
