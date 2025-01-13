/*
* Tangible User Interface class - CIID
* written by Pierluigi Dalla Rosa (www.pierdr.com)
* Teaching with Massimo Banzi and Jose Chavarria
* 
* This sketch introduces you to controlling a motor!
* It makes the motor move back and forth, 
* helping you understand basic motor control.
*/

#include "Motor.h"
// Standard pin mappings for Arduino Motor Shield Rev3
Motor motorA(3, 12, 9);  // PWM on pin 3, Direction on pin 12, Brake on pin 9
// Motor motorB(11, 13, 8);  // PWM on pin 11, Direction on pin 13, Brake on pin 8



void setup() {
  intiSerial();

  motorA.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Run motor A forward at half speed
  motorA.forward(120);

  delay(1000);

  // Disable motor
  motorA.disable();

  delay(1000);

  // Release brakes and set speeds directly
  motorA.enable();

  // Can also use setSpeed with positive/negative values
  motorA.setSpeed(-120);  // Backward at about 78% speed


  delay(1000);
}
