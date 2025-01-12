/*
* This program implements a BLDC motor control system that incrementally increases
* the torque value every 6 seconds, resetting to 0 when it reaches 6. 
* Tangible User Interface class - CIID
* written by Pierluigi Dalla Rosa (www.pierdr.com)
* Teaching with Massimo Banzi and Jose Chavarria
* 
*** Notes 
* 1. check the motor voltage from your power supply
* 2. find your pole pairs for your motor using the sketch find_pole_pairs_number.ino
*/

#include <SimpleFOC.h>

/***************** HARDWARE CONFIGURATION *****************/
#define MOTOR_VOLTAGE 9
#define MOTOR_POLE_PAIRS 7
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
BLDCMotor motor = BLDCMotor(MOTOR_POLE_PAIRS);
BLDCDriver3PWM driver = BLDCDriver3PWM(9, 5, 6, 8);


/***************** CONTROL PARAMETERS *****************/
#define INTERVAL 60000  // Interval for torque increment in milliseconds

/***************** STATE VARIABLES *****************/
float torque_value = 0;
float working_angle = 0;
unsigned long last_event = 0;
bool move_forward = false;

void setup() {
    initSerial();
    initMotor();
    
   
}

void loop() {
    motor.loopFOC();
    motor.move(torque_value);
    working_angle = sensor.getSensorAngle();
    
    if(millis() - last_event > INTERVAL) {
        torque_value += 0.5;
        if(torque_value > 6) {
            torque_value = 0;
        }
        Serial.println(torque_value);
        last_event = millis();
    }
}
