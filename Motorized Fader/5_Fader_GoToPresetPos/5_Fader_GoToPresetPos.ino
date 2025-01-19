/*
* Tangible User Interface class - CIID
* Written by Jose Chavarria
* Teaching with Massimo Banzi and Pierluigi Dalla Rosa
* 
* This sketch introduces you to controlling a motorized slider
* The user is able to move the slider to a pre fixed position
* stored in a position array. 
* By pressing a button, the user is able to navigate the array.
*/

// Pin Definitions
#define MOTOR_IN1 5    // Motor control pin 1
#define MOTOR_IN2 6    // Motor control pin 2
#define PWM_PIN 9      // Speed control pin for the motor
#define BUTTON_PIN 7   // Digital input for button control
#define SLIDER_PIN A1  // Analog input from slider's feedback potentiometer

// Control Parameters
#define MOTOR_SPEED 120                // Default motor speed (PWM value 0-255)
#define MAX_SLIDER 1023                // Maximum value from analog read
#define MARGIN_ERROR MAX_SLIDER / 100  // Acceptable position error (±1% of max range)
#define DEBOUNCE_DELAY 500             // Button debounce delay in milliseconds

// Function Declarations
void motorStop();
void motorForward(int speed);
void motorBackward(int speed);

// Predefined positions for the slider (0-1023 range)
const int PRESET_POSITIONS[] = { 0, 750, 200, 500, 1000 };
const int ARRAY_SIZE = sizeof(PRESET_POSITIONS) / sizeof(PRESET_POSITIONS[0]);

// State tracking variables
int currentTarget = 0;  // Index for current target position in PRESET_POSITIONS

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Configure input/output pins
  pinMode(BUTTON_PIN, INPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  // Ensure motor is stopped when the system starts
  motorStop();
}

void loop() {
  // Get current target position from preset array
  int targetVal = PRESET_POSITIONS[currentTarget];

  // Read current position from slider feedback
  int sliderVal = analogRead(SLIDER_PIN);

  // Read button state for position selection
  int buttonVal = digitalRead(BUTTON_PIN);

  // Handle button press with debounce
  if (buttonVal == HIGH) {
    // Increment target position index
    currentTarget++;

    // Wrap around to start if we've reached the end
    if (currentTarget >= ARRAY_SIZE) {
      currentTarget = 0;
    }

    // Debounce delay to prevent multiple triggers
    delay(DEBOUNCE_DELAY);
  }

  // Compare current position with target, accounting for acceptable error range
  if (sliderVal > targetVal + MARGIN_ERROR) {
    // Current position is too far forward - move backward
    motorBackward(MOTOR_SPEED);
  } else if (sliderVal < targetVal - MARGIN_ERROR) {
    // Current position is too far back - move forward
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

void motorForward(int speed) {
  // Set motor direction to forward and apply speed
  analogWrite(PWM_PIN, speed);
  digitalWrite(MOTOR_IN2, HIGH);
  digitalWrite(MOTOR_IN1, LOW);
}

void motorBackward(int speed) {
  // Set motor direction to backward and apply speed
  analogWrite(PWM_PIN, speed);
  digitalWrite(MOTOR_IN2, LOW);
  digitalWrite(MOTOR_IN1, HIGH);
}
