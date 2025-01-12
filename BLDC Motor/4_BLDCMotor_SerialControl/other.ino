
void processSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    
    // Parse command structure: MODE,VALUE
    // MODE: 'P' for position, 'T' for torque
    // VALUE: float number
    
    char mode = command.charAt(0);
    float value = command.substring(2).toFloat();
    
    switch (mode) {
      case 'P':  // Position control
        position_control = true;
        moveToAngle(value);
        break;
        
      case 'T':  // Torque control
        position_control = false;
        torque_value = value;
        break;
    }
  }
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


