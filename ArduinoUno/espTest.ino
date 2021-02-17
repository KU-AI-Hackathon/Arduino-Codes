#include <SoftwareSerial.h> //SoftwareSerial 사용을 위함
#include <ESP8266.h>        //다운 후 libraries폴더에 저장한 라이브러리
 
//SoftwareSerial(RX, TX)
//RX(D2): ESP8266의 TX 연결
//TX(D3): ESP8266의 RX 연결
SoftwareSerial esp8266Serial = SoftwareSerial(2, 3); // RX TX
ESP8266 wifi = ESP8266(esp8266Serial);
 
#define SSID "KT_GiGA_2G_Wave2_9EBD" // SSid
#define PWD "6bg90dk422" // SSid pw
#define IP "172.30.1.30:4000" // 접근할 웹 서버 IP
 
void setup()
{
  Serial.begin(9600);
  esp8266Serial.begin(9600);  // ESP8266

  if(esp8266Serial.isListening())
    Serial.println("esp8266Serial Listening");
    if(esp8266Serial.available())
    Serial.println("esp8266Serial Available");
 
  wifi.begin();
  wifi.setTimeout(1000);
 
  /****************************************/
  /******       Basic commands       ******/
  /****************************************/
  // test
  Serial.print("test: ");
  Serial.println(getStatus(wifi.test()));
 
  // restart
  Serial.print("restart: ");
  Serial.println(getStatus(wifi.restart()));
 
  // getVersion
  char version[16] = {};
  Serial.print("getVersion: ");
  Serial.print(getStatus(wifi.getVersion(version, 16)));
  Serial.print(" : ");
  Serial.println(version);
 
  /****************************************/
  /******        WiFi commands       ******/
  /****************************************/
  // setWifiMode
  Serial.print("setWifiMode: ");
  Serial.println(getStatus(wifi.setMode(ESP8266_WIFI_STATION)));
 
  // quitAP
  Serial.print("quitAP: ");
  Serial.println(getStatus(wifi.quitAP()));
 
  // joinAP
  Serial.print("joinAP: ");
  Serial.println(getStatus(wifi.joinAP(SSID, PWD)));
 
  // getAP
  Serial.print("getAP: ");
  Serial.println(getStatus(wifi.getAP(SSID)));
 
  /****************************************/
  /******       TCP/IP commands      ******/
  /****************************************/
  // connect with webserver 
  Serial.print("connect: ");
  Serial.println(getStatus(wifi.connect(ESP8266_PROTOCOL_TCP, IPAddress(10, 15, 0, 136), 3000)));
  getConnectionStatue(wifi);
 
  // send to webserver
  Serial.print("send: ");
 // 2줄을 띄워줘야 함(\r\n\r\n)
  Serial.println(getStatus(wifi.send("GET /process/login?id=inbin HTTP/1.0\r\n\r\n")));
}
 
void loop()
{
  // read data
  unsigned int id;
  int length;
  int totalRead;
  char buffer[11] = {};
  if ((length = wifi.available()) > 0) {
    id = wifi.getId();
    totalRead = wifi.read(buffer, 1000);
    if (length > 0) {
      Serial.println((char*)buffer);
    }
  }
}
 
void getConnectionStatue(ESP8266 wifi) {
  // getConnectionStatus
  ESP8266ConnectionStatus connectionStatus;
  ESP8266Connection connections[5];
  unsigned int connectionCount;
  Serial.print("getConnectionStatus: ");
  Serial.print(getStatus(wifi.getConnectionStatus(connectionStatus, connections, connectionCount)));
  Serial.print(" : ");
  Serial.println(connectionCount);
  for (int i = 0; i < connectionCount; i++) {
    Serial.print(" - Connection: ");
    Serial.print(connections[i].id);
    Serial.print(" - ");
    Serial.print(getProtocol(connections[i].protocol));
    Serial.print(" - ");
    Serial.print(connections[i].ip);
    Serial.print(":");
    Serial.print(connections[i].port);
    Serial.print(" - ");
    Serial.println(getRole(connections[i].role));
  }
}
 
String getStatus(bool status)
{
  if (status)
    return "OK";
 
  return "KO";
}
 
String getStatus(ESP8266CommandStatus status)
{
  switch (status) {
    case ESP8266_COMMAND_INVALID:
      return "INVALID";
      break;
 
    case ESP8266_COMMAND_TIMEOUT:
      return "TIMEOUT";
      break;
 
    case ESP8266_COMMAND_OK:
      return "OK";
      break;
 
    case ESP8266_COMMAND_NO_CHANGE:
      return "NO CHANGE";
      break;
 
    case ESP8266_COMMAND_ERROR:
      return "ERROR";
      break;
 
    case ESP8266_COMMAND_NO_LINK:
      return "NO LINK";
      break;
 
    case ESP8266_COMMAND_TOO_LONG:
      return "TOO LONG";
      break;
 
    case ESP8266_COMMAND_FAIL:
      return "FAIL";
      break;
 
    default:
      return "UNKNOWN COMMAND STATUS";
      break;
  }
}
 
String getRole(ESP8266Role role)
{
  switch (role) {
    case ESP8266_ROLE_CLIENT:
      return "CLIENT";
      break;
 
    case ESP8266_ROLE_SERVER:
      return "SERVER";
      break;
 
    default:
      return "UNKNOWN ROLE";
      break;
  }
}
 
String getProtocol(ESP8266Protocol protocol)
{
  switch (protocol) {
    case ESP8266_PROTOCOL_TCP:
      return "TCP";
      break;
 
    case ESP8266_PROTOCOL_UDP:
      return "UDP";
      break;
 
    default:
      return "UNKNOWN PROTOCOL";
      break;
  }
}
