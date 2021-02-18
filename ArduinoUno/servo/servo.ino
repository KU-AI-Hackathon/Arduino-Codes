#include <Servo.h>

Servo servo;
int angle = 0; //각도 조절 변수 value

void setup(){
  servo.attach(7);    //attach : 핀 설정
  Serial.begin(9600);  
}

void loop(){
  for (angle = 0;angle<=90;angle+=1){
  delay(10000);
  servo.write(angle);
  }
  for (angle = 180;angle>=90;angle-=1){
  delay(10000);
  servo.write(angle);
  }
}
