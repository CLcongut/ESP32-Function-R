#include <Arduino.h>
#include <WIFI.h>

#define wifi_SSID "副WLW"       // WIFI名字，不可中文
#define wifi_PSWD "WLW11223344" // WIFI密码，不可中文，最好 8 位

WiFiUDP udp;
int cnt = 0;

IPAddress remote_IP(192, 168, 4, 2);

unsigned int remoteUdpPort = 6060;

char incomingPacket[255]; // 存储Udp客户端发过来的数据

void setup()
{
  Serial.begin(115200);

  WiFi.softAP("esp32_udp_server");

  // WiFi.mode(WIFI_STA);
  // WiFi.setSleep(false); // 关闭STA模式下wifi休眠，提高响应速度
  // WiFi.begin(wifi_SSID, wifi_PSWD);
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(200);
  //   Serial.println(".");
  // }
  // Serial.print("Connected, IP Address: ");
  // Serial.println(WiFi.localIP());

  udp.begin(remoteUdpPort);
}

void loop()
{
  int Data_length = udp.parsePacket(); // 获取接收的数据的长度
  if (Data_length)                     // 如果有数据那么Data_length不为0，无数据Data_length为0
  {
    int len = udp.read(incomingPacket, 255); // 读取数据，将数据保存在数组incomingPacket中
    if (len > 0)                             // 为了避免获取的数据后面乱码做的判断
    {
      incomingPacket[len] = 0;
    }

    /*将接受到的数据发送回去*/
    udp.beginPacket(udp.remoteIP(), udp.remotePort()); // 准备发送数据到目标IP和目标端口
    udp.print("receive data:");                        // 将数据receive data:放入发送的缓冲区
    udp.println(incomingPacket);                       // 将接收到的数据放入发送的缓冲区
    udp.endPacket();                                   // 向目标IP目标端口发送数据
  }
}
