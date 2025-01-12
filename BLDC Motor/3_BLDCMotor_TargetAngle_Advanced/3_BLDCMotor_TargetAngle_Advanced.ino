/*
* PID Motor Control with Continuous Rotation
* Tangible User Interface class - CIID
* written by Pierluigi Dalla Rosa (www.pierdr.com)
* Teaching with Massimo Banzi and Jose Chavarria
*
* This program implements PID control for precise BLDC motor positioning.
* The motor continuously rotates by small increments (3 degrees) simulating a clock,
* with options for automatic shortest path or manual direction control.
*/

#include <SimpleFOC.h>

/***************** HARDWARE CONFIGURATION *****************/
#define MOTOR_VOLTAGE 9
#define MOTOR_POLE_PAIRS 7
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
BLDCMotor motor = BLDCMotor(7);
BLDCDriver3PWM driver = BLDCDriver3PWM(9, 5, 6, 8);

/***************** CONTROL PARAMETERS *****************/
enum RotationDirection {
    CLOCKWISE = 1,
    ANTICLOCKWISE = -1
};

const float Kp = 3.0f;    // Proportional gain - Higher values = faster response
const float Ki = 10.0f;    // Integral gain - Higher values = better steady-state
const float Kd = 0.0f;     // Derivative gain - Higher values = more damping
const float max_torque = 2.0f;

/***************** STATE VARIABLES *****************/
float target_angle = 0.0f;
float desired_target = 0.0f;
float integral_error = 0.0f;
float last_error = 0.0f;
bool manual_direction = false;
RotationDirection motor_direction = CLOCKWISE;


/***************** OTHERS *****************/
unsigned long time_since_last_event = 0;
unsigned long last_print = 0;

void setup() {

  initSerial();
  initMotor();
}

void loop() {
    motor.loopFOC();
    updateAngleControl();

    // Increment target angle every 1 second
    if(millis() - time_since_last_event > 16000) {
        time_since_last_event = millis();
        desired_target += (PI/60);  // 3 degrees increment
        moveToAngle(desired_target);
    }

   
    if (millis() - last_print > 1000) {
        Serial.print("Target: ");
        Serial.print(target_angle);
        Serial.print(" Current: ");
        Serial.print(sensor.getMechanicalAngle());
        Serial.print(" Error: ");
        Serial.println(last_error);
        last_print = millis();
    }
}