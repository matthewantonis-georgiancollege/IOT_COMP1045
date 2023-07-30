// Lab 10 Level 4 Completed
// Matthew Antonis
// 2023-03-30
// Arduino 1

#include <Wire.h>

const int BUTTON1_PIN = 2;
const int BUTTON2_PIN = 3;

volatile bool button1Pressed = false;
volatile bool button2Pressed = false;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)

  attachInterrupt(digitalPinToInterrupt(BUTTON1_PIN), button1ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON2_PIN), button2ISR, RISING);
}

void loop() {
  if (button1Pressed) {
    Wire.beginTransmission(4);       // transmit to device #4
    Wire.write(1);                   // sends message "1"
    Wire.endTransmission();          // stop transmitting
    button1Pressed = false;
  }

  if (button2Pressed) {
    Wire.beginTransmission(4);       // transmit to device #4
    Wire.write(2);                   // sends message "2"
    Wire.endTransmission();          // stop transmitting
    button2Pressed = false;
  }

  delay(50); // debounce delay
}

void button1ISR() {
  button1Pressed = true;
}

void button2ISR() {
  button2Pressed = true;
}