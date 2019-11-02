const int trigPin1 = 12;//입구쪽 센서

const int echoPin1 = 11;

const int trigPin2 = 10;//출구쪽 센서

const int echoPin2 = 9;

int count1,count2 = 0;

int inCount = 0;

int outCount = 0;

int nowCount = 0;//초기 주차장 차량 수

void setup(){
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

  if(distance1 < 15){
    
    count1++;
   
  }
  if(count1 > 1 && distance1 >25){

    inCount++;

    count1 = 0;
  }

  if(distance2 < 15){
     count2++;
  }
  if(count2 > 1 && distance2 > 25){
    outCount++;

    count2 = 0;
  }
  Serial.print(nowCount + inCount - outCount);
  Serial.println(" 대");

  delay(500);
  
}
