/* 
 * Tangible User Interface class - CIID
 * written by Pierluigi Dalla Rosa (www.pierdr.com)
 * Teaching with Massimo Banzi and Jose Chavarria
 * 
 * This sketch makes your smooth fader feel like it has
 * 16 distinct positions - like a slider with invisible
 * notches that you can feel.
 */

#include "Motor.h"

#define MOTOR_MIN 0           // Minimum sensor reading
#define MOTOR_MAX 512        // Maximum sensor reading
#define POSITION_THRESHOLD 2  // Dead zone for position control
#define FADER_PIN A2          // Analog input for fader position
#define MOTOR_SPEED_MAX 255   // Maximum motor speed

/****  DETENT  ****/
int detent_size = (MOTOR_MAX-MOTOR_MIN)/16 ;
int prev_detent_position;

Motor motor(3, 12, 9);

int target_position;
int last_error;


const float Kp = 5.0;  // Proportional gain

void setup() {

   initSerial();
  motor.begin();
  motor.enable();


}

void loop() {
  // put your main code here, to run repeatedly:
  updateMotorControl();
}
