// Lab 10 Level 3 Completed
// Matthew Antonis
// 2023-03-23

#include <Servo.h>

Servo myServo;

int buttonPin1 = 2;
int buttonPin2 = 3;
int angle = 0;

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup(){
  attachInterrupt(digitalPinToInterrupt(buttonPin1),CounterClockwise,RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPin2),Clockwise,RISING);
  Serial.begin(9600);
  myServo.attach(4);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop(){
  myServo.write(angle);
  if(angle == 0){
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  else if(angle == 45){
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  else if(angle == 90){
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
  }
  else if(angle == 135) {
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  else if(angle == 180){
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
  }
  else if (angle >180){
    for (int i = 0;i<5;i++){
     angle -= 45;
     myServo.write(angle);
     delay(200);
    
    if(angle == 180)
    {
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    }
    else if(angle == 135) {
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
   else if(angle == 90){
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
  }
    else if(angle == 45){
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
   else if(angle == 0){
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }     
  }
  }
  else if(angle <0){
    for (int i = 0;i<5;i++){
     angle += 45;
     myServo.write(angle);
     delay(200);
      
    if(angle == 0){
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  else if(angle == 45){
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  else if(angle == 90){
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
  }
  else if(angle == 135) {
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  else if(angle == 180){
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
  }
  }
  }
}

void CounterClockwise(){
angle += 45;
}

void Clockwise(){
  angle -= 45;
}