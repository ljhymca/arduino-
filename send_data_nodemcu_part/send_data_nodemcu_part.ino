
#include <FirebaseArduino.h>
#include <FirebaseHttpClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

#define FIREBASE_HOST "arduino-bc9bb.firebaseio.com"
#define FIREBASE_AUTH "FAcpzLYgCysO43BfzNkz0GRxooYvbG3o2Bv28vkp"
//#define WIFI_SSID "KBU"
//#define WIFI_PASSWORD "1952bible!"
SoftwareSerial s(D6,D5);
int sendCount;
const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

const char* ssid = "KBU";
const char* password = "1952bible!";

const char* host = "210.123.254.175";

WiFiClient client;
const int httpPort = 80;
String url;

void setup() {
  // put your setup code here, to run once:
  s.begin(9600);
  Serial.begin(9600);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  while(!Serial)continue;
  delay(10);

  // Connect to WiFi network

  Serial.println();

  Serial.println();

  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

 

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

void loop() {

   unsigned long currentTime = millis();
   
   if(currentTime - previousTime >= eventInterval){
   Serial.print("connecting to ");
   Serial.println(host);

   if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
   }

   sendCount=s.read();

   Firebase.setInt("sendCount", sendCount);

   if (Firebase.failed()) { 
      Serial.print("setting /number failed:"); 
      Serial.println(Firebase.error());   
      delay(500);
      return; 
  }
   
   Serial.print(sendCount);
   Serial.println(" 대"); 

   url = "/CHO/index.php/CHO/sensor?data=";
   url += sendCount;

   Serial.print("Requesting URL: ");
   Serial.println(url);

   client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

   while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
   }
   
   Serial.println();
   Serial.println("closing connection");
   Serial.println();

   previousTime = currentTime;
   }

}
