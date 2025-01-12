/*
* Angle Control from Processing
* Tangible User Interface class - CIID
* written by Pierluigi Dalla Rosa (www.pierdr.com)
* Teaching with Massimo Banzi and Jose Chavarria
*
* This program implements a simple motor control using the serial port
* There is a companion sketch that creates an interface in Processing
*/

#include <SimpleFOC.h>

/***************** HARDWARE CONFIGURATION *****************/
#define MOTOR_VOLTAGE 9
#define MOTOR_POLE_PAIRS 7
// Pin definitions
const int PIN_PWM_A = 9;
const int PIN_PWM_B = 5;
const int PIN_PWM_C = 6;
const int PIN_ENABLE = 8;

// Motor and sensor instances
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
BLDCMotor motor = BLDCMotor(MOTOR_POLE_PAIRS);
BLDCDriver3PWM driver = BLDCDriver3PWM(PIN_PWM_A, PIN_PWM_B, PIN_PWM_C, PIN_ENABLE);


/***************** CONTROL PARAMETERS *****************/
const float Kp = 3.0f;

/***************** STATE VARIABLES *****************/
float target_angle = 0.0f; // degrees
float torque_value = 0;    
bool position_control = false;

void setup() {
 initSerial();
 initMotor();
}

void loop() {
  // Main FOC loop
  motor.loopFOC();
  sensor.update();
  // Check for serial commands
  processSerialCommands();
  
  // Apply motor control
  if (position_control) {
    updateAngleControl();
  } else {
    motor.controller = MotionControlType::torque;
    motor.move(torque_value);
  }
  
}

