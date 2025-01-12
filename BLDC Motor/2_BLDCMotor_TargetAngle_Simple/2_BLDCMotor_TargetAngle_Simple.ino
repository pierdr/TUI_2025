/*
* Angle Control for Motors - Position Lock Example
* Tangible User Interface class - CIID
* written by Pierluigi Dalla Rosa (www.pierdr.com)
* Teaching with Massimo Banzi and Jose Chavarria
*
* This program implements a simple proportional control for a BLDC motor
* to maintain a fixed angular position. When started, the motor moves to
* a target position and holds that position.
*/

#include <SimpleFOC.h>

/***************** HARDWARE CONFIGURATION *****************/
#define MOTOR_VOLTAGE 9
#define MOTOR_POLE_PAIRS 7
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
BLDCMotor motor = BLDCMotor(MOTOR_POLE_PAIRS);
BLDCDriver3PWM driver = BLDCDriver3PWM(9, 5, 6, 8);

/***************** CONTROL PARAMETERS *****************/
const float Kp = 3.0f;

/***************** STATE VARIABLES *****************/
float target_angle = 0.0f;
bool did_start = false;

void setup() {

  initSerial();
  initMotor();
}


void moveToAngle(float target) {
    target_angle = target;
}


void updateAngleControl() {
    float current_angle = sensor.getMechanicalAngle();
    float error = target_angle - current_angle;
    float control_output = Kp * error;
    motor.move(control_output);
}



void loop() {
    motor.loopFOC();
    updateAngleControl();
    
    if(!did_start) {
        moveToAngle(PI);
        did_start = true;
    }
}