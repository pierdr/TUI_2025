void initMotor() {
  sensor.init();
  motor.linkSensor(&sensor);

  // Configure driver
  driver.voltage_power_supply = MOTOR_VOLTAGE;
  driver.init();
  motor.linkDriver(&driver);

  // Configure motor control parameters
  motor.controller = MotionControlType::torque;
  motor.voltage_limit = 6;
  motor.velocity_limit = 20;
  motor.useMonitoring(Serial);

  // Initialize motor control
  motor.init();
  motor.initFOC();
  motor.loopFOC();
}

void initSerial()
{
  Serial.begin(115200);
    Serial.println("started");
}