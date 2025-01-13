/*
 *
 * Motor control for use with the Arduino Motor Shield Rev3 or compatible shields
 *
 * Tangible User Interface class - CIID
 * written by Pierluigi Dalla Rosa (www.pierdr.com)
 * Teaching with Massimo Banzi and Jose Chavarria
 */
 



#include "Motor.h"


// Motor.cpp implementation
Motor::Motor(int pwmPin, int dirPin, int enablePin) {
    _pwmPin = pwmPin;
    _dirPin = dirPin;
    _enablePin = enablePin;
    _currentSpeed = 0;
}

void Motor::begin() {
    pinMode(_pwmPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    
    // Initialize with motor stopped and enable released
    digitalWrite(_enablePin, LOW);
    analogWrite(_pwmPin, 0);
    digitalWrite(_dirPin, LOW);
}

void Motor::setSpeed(int speed) {
    // Constrain speed to valid range
    speed = constrain(speed, -255, 255);
    _currentSpeed = speed;
    
    if (speed >= 0) {
        digitalWrite(_dirPin, HIGH);  // Forward
        analogWrite(_pwmPin, speed);
    } else {
        digitalWrite(_dirPin, LOW);   // Backward
        analogWrite(_pwmPin, -speed);
    }
}

int Motor::getSpeed() {
    return _currentSpeed;
}

void Motor::forward(int speed) {
    speed = constrain(speed, 0, 255);
    digitalWrite(_dirPin, HIGH);
    analogWrite(_pwmPin, speed);
    _currentSpeed = speed;
}

void Motor::backward(int speed) {
    speed = constrain(speed, 0, 255);
    digitalWrite(_dirPin, LOW);
    analogWrite(_pwmPin, speed);
    _currentSpeed = -speed;
}

void Motor::disable() {
    digitalWrite(_enablePin, HIGH);
    analogWrite(_pwmPin, 0);
    _currentSpeed = 0;
}

void Motor::enable() {
    digitalWrite(_enablePin, LOW);
}