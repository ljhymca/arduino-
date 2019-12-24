#include <SoftwareSerial.h>
//#include <ArduinoJson.h>
SoftwareSerial s(5,6);

const int trigPin1 = 12;//입구쪽 센서

const int echoPin1 = 11;

const int trigPin2 = 10;//출구쪽 센서

const int echoPin2 = 9;

int count1,count2 = 0;

int inCount = 0;//입차 수

int outCount = 0;//출차 수

int nowCount = 53;//초기 주차장 차량 수 꼭 시작전에 수정할 것

void setup(){
  s.begin(9600);
  Serial.begin(9600);
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
}

void loop()
{
  long duration1, distance1, duration2, distance2;

  digitalWrite(trigPin1, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin1, HIGH);
  
  delayMicroseconds(5);

  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);

  digitalWrite(trigPin2, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin2, HIGH);
  
  delayMicroseconds(5);

  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);

  distance1 = (duration1/2) / 29.1;
  distance2 = (duration2/2) / 29.1; //거리구하는 공식

/*
  if(distance1>95 && distance1 < 250){//입차쪽 계산법
    
    count1++;
   
  }
  if(count1 > 1 && distance1 > 250){

    inCount++;

    count1 = 0;
  }

  if(distance2 <= 200){//출차쪽 계산법
     count2++; 
  }
  if(count2 > 1 && distance2 > 250){
    outCount++;

    count2 = 0;
  }

  */
  if(distance1 < 3){//입차쪽 계산법
    
    count1++;
   
  }
  if(count1 > 1 && distance1 > 3){

    inCount++;

    count1 = 0;
  }

  if(distance2 <= 3){//출차쪽 계산법
     count2++;
  }
  if(count2 > 1 && distance2 > 3){
    outCount++;

    count2 = 0;
  }
  
  
  int sendCount = nowCount + inCount - outCount;
  Serial.print(sendCount);
  Serial.println(" 대");
  Serial.print("입차:");
  Serial.println(inCount);
  Serial.print("출차:");
  Serial.println(outCount);
  
  s.write(sendCount);

  delay(1000);
}
