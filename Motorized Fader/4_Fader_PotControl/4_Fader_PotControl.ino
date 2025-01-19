/*
* Tangible User Interface class - CIID
* Written by Jose Chavarria
* Teaching with Massimo Banzi and Pierluigi Dalla Rosa
* 
* This sketch introduces you to controlling a motorized slider
* The user is able to move the slider with the use of a potentiometer
*/

// Pin Definitions
#define MOTOR_IN1 5    // Motor control pin 1
#define MOTOR_IN2 6    // Motor control pin 2
#define PWM_PIN 9      // Speed control pin for the motor
#define SLIDER_PIN A1  // Analog input from slider's feedback potentiometer
#define POT_PIN A0     // Analog input from control potentiometer

// Control Parameters
#define MAX_SLIDER 1023                // Maximum value from analog read (10-bit ADC)
#define MARGIN_ERROR MAX_SLIDER / 100  // Acceptable position error (±1% of max range)
#define MOTOR_SPEED 120                // Fixed motor speed (PWM value 0-255)


void setup() {
  // Initialize serial communication for debugging (9600 baud rate)
  Serial.begin(115200);

  // Configure motor control pins as outputs
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  // Ensure motor is stopped when the system starts
  motorStop();
}

void loop() {
  // Read the target position from the control potentiometer (0-1023)
  int potVal = analogRead(POT_PIN);

  // Read the current position from the slider's feedback potentiometer (0-1023)
  int sliderVal = analogRead(SLIDER_PIN);

  // Position control logic
  // Uses a deadband (MARGIN_ERROR) to prevent oscillation around target position
  if (sliderVal > potVal + MARGIN_ERROR) {
    // Current position is too far forward - move backward
    //analogWrite(PWM_PIN, MOTOR_SPEED);
    motorBackward(MOTOR_SPEED);
  } else if (sliderVal < potVal - MARGIN_ERROR) {
    // Current position is too far back - move forward
    //analogWrite(PWM_PIN, MOTOR_SPEED);
    motorForward(MOTOR_SPEED);
  } else {
    // Within acceptable range - stop motor
    motorStop();
  }
}

// Motor Control Functions
void motorStop() {
  // Brake motor by setting both inputs HIGH
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, HIGH);
}

// Set motor direction to forward
void motorForward(int speed) {
  // Set motor speed
  analogWrite(PWM_PIN, speed);
  // IN2 HIGH, IN1 LOW moves motor in forward direction
  digitalWrite(MOTOR_IN2, HIGH);
  digitalWrite(MOTOR_IN1, LOW);
}

// Set motor direction to backward
void motorBackward(int speed) {
  // Set motor speed
  analogWrite(PWM_PIN, speed);
  // IN2 LOW, IN1 HIGH moves motor in backward direction
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN1, HIGH);
}
