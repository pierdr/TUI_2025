void initSerial() {
  Serial.begin(115200);
  Serial.println("Motor test - Fader");
}
int calculateMotorSpeed(int error, int currentPos) {
  // Simple PD control
  float derivative = error - last_error;
  float output = -Kp * error + Kd * derivative;
  // float output = -Kp * error;
  last_error = error;

  // Convert to motor speed and constrain
  int motorSpeed = (int)output;
  return constrain(motorSpeed, -MOTOR_SPEED_MAX, MOTOR_SPEED_MAX);
}
void moveToPos(int newPos) {
  // Constrain target position to valid range
  target_position = constrain(newPos, MOTOR_MIN, MOTOR_MAX);
}

void updateMotorControl() {
  int currentPos = analogRead(FADER_PIN);
  int error = target_position - currentPos;

  // If within threshold, stop motor
  if (abs(error) < POSITION_THRESHOLD) {
    motor.setSpeed(0);
    return;
  }

  // Calculate and set motor speed
  int speed = calculateMotorSpeed(error, currentPos);
  motor.setSpeed(speed);
}