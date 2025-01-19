/*
* Tangible User Interface class - CIID
* written by Pierluigi Dalla Rosa (www.pierdr.com)
* Modified by Jose Chavarria 19/01/2024
* Teaching with Massimo Banzi and Jose Chavarria
* 
* This sketch introduces you to controlling a motor!
* It makes the motor move back and forth, 
* helping you understand basic motor control.
*/

#include "Motor.h"
// Standard pin mappings for Arduino Motor Shield Rev3
Motor motorA(3, 12, 9);  // Speed on pin 3, Motor Control 1 pin 12, Motor Control 2 on pin 9



void setup() {
  intiSerial();

  motorA.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Run motor A forward at half speed
  motorA.forward(120);

  delay(100);

  // Disable motor
  motorA.disable();

  delay(1000);

  // Release brakes and set speeds directly
  motorA.enable();

  // Can also use setSpeed with positive/negative values
  motorA.backward(120);  // Backward at about 78% speed


  delay(100);
  // Disable motor
  motorA.disable();

  delay(1000);
}
