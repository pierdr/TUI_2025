void updateAngleControl() {
    // Get current angle
    float current_angle = normalizeAngle(sensor.getMechanicalAngle());
    
    // Calculate error based on control mode
    float error;
    if (manual_direction) {
        error = calculateForcedDirectionPath(current_angle, target_angle, motor_direction);
    } else {
        error = calculateShortestPath(current_angle, target_angle);
    }
    
    // PID control implementation
    float dt = 0.001f; // Assuming 1ms control loop - adjust as needed
    integral_error += error * dt;
    float derivative_error = (error - last_error) / dt;
    
    // Calculate control output
    float control_output = Kp * error + Ki * integral_error + Kd * derivative_error;
    
    // Limit control output to motor's torque limits
    float maxTorque = 2.0f; // Adjust based on your motor's capabilities
    control_output = constrain(control_output, -max_torque, max_torque);
    
    // Apply control to motor
    motor.move(control_output);
    
    // Store error for next iteration
    last_error = error;
}
float normalizeAngle(float angle) {
    // Normalize angle to [0, 2π]
    
    while (angle < 0) angle += TWO_PI;
    while (angle >= TWO_PI) angle -= TWO_PI;
    return angle;
}

float calculateShortestPath(float currentAngle, float targetAngle) {
    
    float error = targetAngle - currentAngle;
    
    // Normalize error to [-π, π]
    while (error > PI) error -= TWO_PI;
    while (error < -PI) error += TWO_PI;
    
    return error;
}

float calculateForcedDirectionPath(float currentAngle, float targetAngle, RotationDirection direction) {
    
    float error = targetAngle - currentAngle;
    
    // Adjust error based on forced direction
    if (direction == CLOCKWISE) {
        while (error < 0) error += TWO_PI;
    } else {
        while (error > 0) error -= TWO_PI;
    }
    
    return error;
}

void moveToAngle(float target) {
    target_angle = normalizeAngle(target);
}
float fRadians(float deg) {
    // Define pi or use the M_PI constant from math.h
    
    // Convert degrees to radians
    return deg * (PI / 180.0f);
}
