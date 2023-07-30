// Lab 9 Level 4 
// Matthew Antonis
// 2023-03-16

#include <IRremote.h>
#define IR_RECEIVE_PIN 11
#define btn1 16
#define btn2 17
#define btn3 18
#define btn4 19
#define btnpwr 0

//variables
int value;
int redPIN = 13;
int bluePIN = 12;
int greenPIN = 9;
bool powerON = false;
int buttonPIN = 10;
int buzzerPIN = 8;
 
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(redPIN, OUTPUT);
  pinMode(bluePIN, OUTPUT);
  pinMode(greenPIN, OUTPUT);
  Serial.println("Please Hit Power to start");
  pinMode(buttonPIN, INPUT);
  pinMode(buzzerPIN, OUTPUT);
}

// Starting selection and power on/off loop
void loop() {
  if (IrReceiver.decode()) {
    value = IrReceiver.decodedIRData.command;
    IrReceiver.resume();

    if (value == btnpwr) {
      powerON = !powerON;
      Serial.println("Welcome!");
      Serial.println("Please press 1, 2, 3, 4 to start");
    }

    if (powerON) {
      if (value == btn1) {
        level1();
      }
      if (value == btn2) {
        level2();
      }
    }
  }
}

// Level 1 loop
void level1() {
  Serial.println("Press 1 To loop the RGB Light");

  while (powerON) {
    if (IrReceiver.decode()) {
      value = IrReceiver.decodedIRData.command;
      IrReceiver.resume();

      if (value == btnpwr) {
        powerON = !powerON;
        Serial.println("Goodbye");
        break;
      }

      if (value == btn1) {
        for (int i = 0; i < 3; i++) {
          digitalWrite(bluePIN, HIGH);
          delay(200);
          digitalWrite(bluePIN, LOW);
          digitalWrite(greenPIN, HIGH);
          delay(200);
          digitalWrite(greenPIN, LOW);
          digitalWrite(redPIN, HIGH);
          delay(200);
          digitalWrite(redPIN, LOW);
        }
      }
    }
  }
}

void level2() {
Serial.println(" "); 
if(digitalRead(buttonPIN)==HIGH){

  } 
}
