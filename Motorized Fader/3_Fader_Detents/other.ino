void initSerial() {
  Serial.begin(115200);
  Serial.println("Fader with detents");
}


   int normalizePosition(int pos) {
        return constrain(pos, MOTOR_MIN, MOTOR_MAX);
    }
    
    int calculateDetentPosition(int currentPos) {
        // Calculate nearest detent position
 
        int detentIndex = (currentPos-MOTOR_MIN) / detent_size ;
   
        return ((detentIndex * detent_size)+detent_size/2) + MOTOR_MIN;
    }

    void updateMotorControl()
    {
       int currentPos = analogRead(FADER_PIN);
        currentPos = normalizePosition(currentPos);
        
         // Calculate desired detent position
        int desired_position = calculateDetentPosition(currentPos);
        
            // Calculate error and direction
            int error = desired_position - currentPos;
            Serial.println(error);
            
            // Apply motor power based on distance from detent
            if (abs(error) < POSITION_THRESHOLD) {
                motor.setSpeed(0);
            } else {
                int speed = constrain(-Kp*error, -MOTOR_SPEED_MAX, MOTOR_SPEED_MAX);
                motor.setSpeed(speed);
            }
        // }
    }