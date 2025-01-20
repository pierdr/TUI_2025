/* 
 * Tangible User Interface class - CIID
 * written by Pierluigi Dalla Rosa (www.pierdr.com)
 * Teaching with Massimo Banzi and Jose Chavarria
 * 
 * Make your fader move to exact an position.
 * This sketch uses something called PD control to move
 * the motor to reach a specific spot.
 */

#include "Motor.h"

#define MOTOR_MIN 0           // Minimum sensor reading
#define MOTOR_MAX 512        // Maximum sensor reading
#define POSITION_THRESHOLD 5  // Dead zone for position control
#define FADER_PIN A2          // Analog input for fader position
#define MOTOR_SPEED_MAX 255   // Maximum motor speed

Motor motor(3, 12, 9);

int target_position;
int last_error;

const float Kp = 10.0;  // Proportional gain
const float Kd = 4.0;  // Derivative gain

void setup() {
  initSerial();
  motor.begin();
  motor.enable();
  moveToPos(300);
}

void loop() {
  updateMotorControl();
}
