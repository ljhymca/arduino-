#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("scan start");

  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n==0)//와이파이가 없을때
    Serial.println("no networks found");
  else{
    Serial.println(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
       Serial.print(i + 1);
       Serial.print(": ");
       Serial.print(WiFi.SSID(i));
       Serial.print(" (");
       Serial.print(WiFi.RSSI(i)); 
       Serial.print(")"); 
       Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*"); 
       delay(10);
    }
  }
  Serial.println("");

  delay(5000);
}
