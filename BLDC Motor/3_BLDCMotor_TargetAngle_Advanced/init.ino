
void initMotor() {
  // put your setup code here, to run once:
  sensor.init();
  motor.linkSensor(&sensor);

  driver.voltage_power_supply = 9;
  driver.init();

  motor.linkDriver(&driver);

  motor.controller = MotionControlType::torque;

  motor.voltage_limit = 6;
  motor.velocity_limit = 20;
  motor.useMonitoring(Serial);
  motor.init();
  motor.initFOC();
  motor.loopFOC();
}
void initSerial() {
  Serial.begin(115200);
  Serial.println("started");
}