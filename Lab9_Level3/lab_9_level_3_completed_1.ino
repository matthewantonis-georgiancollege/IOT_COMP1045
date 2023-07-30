// Lab 9 Level 3 (Completed)
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
bool blueON = false;
bool redON = false;
bool powerON = false;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(redPIN, OUTPUT);
  pinMode(bluePIN, OUTPUT);
  Serial.println("Please Hit Power to start");
}

//Starting selection and power on/off loop
void loop() {
  if (IrReceiver.decode()) {
    value = IrReceiver.decodedIRData.command;
    IrReceiver.resume();

    if (value == btnpwr) {
      powerON = !powerON;
      Serial.println("Welcome!");
      Serial.println("Please press 1, 2 , 3 to choose a level");
    }

    if (powerON) {
      if (value == btn1) {
        level1();
      }
      if (value == btn2) {
        level2();
      }
      if (value == btn3) {
        level3();
      }
    }
  }
}

//level 1 loop
void level1() {
  Serial.println("level 1");
  Serial.println("Press 1 Turn On and Off Blue LED");
  Serial.println("Press 2 Control Red LED");
  Serial.println("Press 3 Control Both LEDs");

  while (powerON) {
    if (IrReceiver.decode()) {
      value = IrReceiver.decodedIRData.command;
      IrReceiver.resume();

      if (value == btnpwr) {
        powerON = !powerON;
        digitalWrite(bluePIN, LOW);
        digitalWrite(redPIN, LOW);
        Serial.println("Goodbye");
        break;
      }

      if (value == btn1) {
        blueON = !blueON;
        digitalWrite(bluePIN, blueON);
        delay(200);
      }
      if (value == btn2) {
        level2();
        break;
      }
      if (value == btn3) {
        level3();
        break;
      }
    }
  }
}

//level 2 loop
void level2() {
  Serial.println("level 2");
  Serial.println("Press 1 Turn On and Off Red LED");
  Serial.println("Press 2 Control Blue LED");
  Serial.println("Press 3 Control Both LEDs");

  while (powerON) {
    if (IrReceiver.decode()) {
      value = IrReceiver.decodedIRData.command;
      IrReceiver.resume();
     
      if (value == btnpwr) {
        powerON = !powerON;
        digitalWrite(bluePIN, LOW);
        digitalWrite(redPIN, LOW);
        Serial.println("Goodbye");
        break;
      }
      if (value == btn1) {
        redON = !redON;
        digitalWrite(redPIN, redON);
        delay(200);
      }
      if (value == btn2) {
        level1();
        break;
      }
      if (value == btn3) {
        level3();
        break;
      }
    }
  }
}

//level 3 loop
void level3() {
  Serial.println("level 3");
  Serial.println("Press 1 Turn Off Both LED");
  Serial.println("Press 2 Control Blue LED");
  Serial.println("Press 3 Control Red LED");

  while (powerON) {
    if (IrReceiver.decode()) {
      value = IrReceiver.decodedIRData.command;
      IrReceiver.resume();

      if (value == btnpwr) {
        powerON = !powerON;
        digitalWrite(bluePIN, LOW);
        digitalWrite(redPIN, LOW);
        Serial.println("Goodbye");
        break;
      }

      if (value == btn1) {
        redON = !redON;
        digitalWrite(redPIN, redON);
        blueON = !blueON;
        digitalWrite(bluePIN, blueON);
        delay(200);
      }
      if (value == btn2) {
        level1();
        break;
      }
      if (value == btn3) {
        level2();
        break;
      }
    }
  }
}





      
      
