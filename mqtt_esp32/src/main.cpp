#include <Arduino.h>
#include <WiFi.h>
#include "PubSubClient.h" ////A client library for MQTT messaging.
#include "DHT.h"
#define DHTPIN 4          // Defines pin number to which the sensor is connected
#define DHTTYPE DHT22     // DHT 22
DHT dht(DHTPIN, DHTTYPE); // Creats a DHT object

/* 连接WIFI SSID和密码 */
#define WIFI_SSID "Redme K5000"
#define WIFI_PASSWD "88888888"

/* 设备的三元组信息*/
#define PRODUCT_KEY "a15ZWaMgl9e"
#define DEVICE_NAME "dht11"
#define DEVICE_SECRET "a543eb715cb8e83f4322f1e1edee1692"
#define REGION_ID "cn-shanghai"

/* 线上环境域名和端口号，不需要改 */
#define MQTT_SERVER PRODUCT_KEY ".iot-as-mqtt." REGION_ID ".aliyuncs.com"
#define MQTT_PORT 1883
#define MQTT_USRNAME DEVICE_NAME "&" PRODUCT_KEY

#define CLIENT_ID "a15ZWaMgl9e.dht11|securemode=2,signmethod=hmacsha256,timestamp=1715170184270|"
#define MQTT_PASSWD "370ee78593144477cbaaae51d2d644fdaf299c6bb1afc378cee70c7d0c11c7f5"

// 宏定义订阅主题
#define ALINK_BODY_FORMAT "{\"id\":\"dht11\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"

unsigned long lastMs = 0;

WiFiClient espClient;
PubSubClient client(espClient);

float soil_data;
float tep;

// 连接wifi
void wifiInit()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("WiFi not Connect");
  }
}

// mqtt连接
void mqttCheckConnect()
{
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT Server ...");
    if (client.connect(CLIENT_ID, MQTT_USRNAME, MQTT_PASSWD))
    {
      Serial.println("MQTT Connected!");
    }
    else
    {
      Serial.print("MQTT Connect err:");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

// 上传温湿度、二氧化碳浓度
void mqttIntervalPost()
{
  char param[32];
  char jsonBuf[128];

  // upload humidity
  soil_data = dht.readHumidity();
  sprintf(param, "{\"Humidity\":%2f}", soil_data);
  sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
  Serial.println(jsonBuf);
  boolean b = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
  if (b)
  {
    Serial.println("publish Humidity success");
  }
  else
  {
    Serial.println("publish Humidity fail");
  }

  // Upload temperature
  tep = dht.readTemperature();
  sprintf(param, "{\"temperature\":%2f}", tep);
  sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
  Serial.println(jsonBuf);
  boolean c = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
  if (c)
  {
    Serial.println("publish Temperature success");
  }
  else
  {
    Serial.println("publish Temperature fail");
  }
}

void setup()
{
  Serial.begin(115200);
  dht.begin();
  wifiInit();
  client.setServer(MQTT_SERVER, MQTT_PORT); /* 连接MQTT服务器 */
}

void loop()
{
  if (millis() - lastMs >= 5000)
  {
    lastMs = millis();
    mqttCheckConnect();
    /* 上报 */
    mqttIntervalPost();
  }
  client.loop();
  delay(2000);
}
