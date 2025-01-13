/*
* PID Motor Control simulating mechanical detents
* Tangible User Interface class - CIID
* written by Pierluigi Dalla Rosa (www.pierdr.com)
* Teaching with Massimo Banzi and Jose Chavarria
*
* This program implements PID control for simulating detents.
*/

#include <SimpleFOC.h>

/***************** HARDWARE CONFIGURATION *****************/
#define MOTOR_VOLTAGE 9
#define MOTOR_POLE_PAIRS 7
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
BLDCMotor motor = BLDCMotor(MOTOR_POLE_PAIRS);
BLDCDriver3PWM driver = BLDCDriver3PWM(9, 5, 6, 8);

/***************** CONTROL PARAMETERS *****************/


const float Kp = 2.0f;   // Proportional gain - Higher values = faster response
const float Ki = 2.0f;  // Integral gain - Higher values = better steady-state
const float Kd = 0.0f;   // Derivative gain - Higher values = more damping
const float max_torque = 2.0f;

/***************** STATE VARIABLES *****************/
float target_angle = 0.0f;
float desired_target = 0.0f;
float integral_error = 0.0f;
float last_error = 0.0f;
float current_angle = 0.0f;
float prev_desired_target = 0.0f;

/***************** DETENTS *****************/
#define NUM_DETENTS 5.0f
float detent_angle =  TWO_PI/NUM_DETENTS;


void setup() {

  initSerial();
  initMotor();
}

void loop() {
  motor.loopFOC();

  // Get current angle
  current_angle = normalizeAngle(sensor.getMechanicalAngle());

  desired_target = floor(current_angle/detent_angle)*detent_angle+detent_angle/2;
  if(prev_desired_target != desired_target)
  {
    moveToAngle(desired_target);
    prev_desired_target = desired_target;
    Serial.print("Target: ");
    Serial.println(desired_target);
  }

  updateAngleControl(current_angle);
 
}