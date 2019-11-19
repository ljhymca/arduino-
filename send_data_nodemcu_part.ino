#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
//#include <ArduinoJson.h>
SoftwareSerial s(D6,D5);
int sendCount;

const char* ssid = "KBU"
const char* pwd = "1952bible!"


void setup() {
  // put your setup code here, to run once:
  s.begin(9600);
  Serial.begin(9600);
  while(!Serial)continue;
}

void loop() {
  // put your main code here, to run repeatedly:
   sendCount=s.read();
   Serial.print(sendCount);
   Serial.println(" 대");
   

//   StaticJsonBuffer<1000> jsonBuffer;
//   JsonObject& root = jsonBuffer.parseObject(s);
//   if (root == JsonObject::invalid())
//      return;
//   Serial.print("들어간 차량 :");
//   int data1=root["data1"];
//   Serial.print("대");   
//   Serial.println("");
   delay(1000);
}
