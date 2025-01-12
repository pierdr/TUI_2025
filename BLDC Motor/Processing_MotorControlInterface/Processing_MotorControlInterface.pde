import controlP5.*;
import processing.serial.*;

Serial arduino;
ControlP5 cp5;
Tab openLoopTab, positionTab;

// Control variables
float torqueValue = 0;
float targetPosition = 0;
boolean isClockwise = true;

void setup() {
  size(400, 800);
  
  // Initialize serial connection
  String portName = Serial.list()[1]; // Modify index as needed
  arduino = new Serial(this, portName, 115200);
  
  // Initialize ControlP5
  cp5 = new ControlP5(this);
  
  // Create tabs
  openLoopTab = cp5.addTab("Open Loop")
    .setColorBackground(color(0, 160, 100))
    .setColorLabel(color(255));
    
  positionTab = cp5.addTab("Position")
    .setColorBackground(color(0, 160, 100))
    .setColorLabel(color(255));
    
  // Open Loop Controls
  cp5.addSlider("torqueIntensity")
    .setPosition(20, 50)
    .setSize(300, 30)
    .setRange(-6, 6)
    .setValue(0)
    .setLabel("Torque Intensity")
    .moveTo(openLoopTab);
    
  cp5.addToggle("rotationDirection")
    .setPosition(50, 100)
    .setSize(20, 20)
    .setLabel("Direction (ON=CW, OFF=CCW)")
    .setValue(true)
    .moveTo(openLoopTab);
    
  // Position Control
  cp5.addSlider("motorPosition")
    .setPosition(20, 50)
    .setSize(300, 30)
    .setRange(0, TWO_PI)
    .setValue(0)
    .setLabel("Target Position (degrees)")
    .moveTo(positionTab);
}

void draw() {
  background(200);
  
  // Update text displays
  fill(0);
  if (cp5.getTab("Open Loop").isActive()) {
    text("Current Torque: " + nf(torqueValue, 0, 2), 50, 200);
    text("Direction: " + (isClockwise ? "Clockwise" : "Counter-clockwise"), 50, 220);
  } else if (cp5.getTab("Position").isActive()) {
    text("Target Position: " + nf(degrees(targetPosition), 0, 1) + " degrees ", 50, 200);
  }
}

// Control event handlers
void torqueIntensity(float value) {
  torqueValue = value * (isClockwise ? 1 : -1);
  sendTorqueCommand(torqueValue);
}

void rotationDirection(boolean value) {
  isClockwise = value;
  torqueValue = abs(torqueValue) * (isClockwise ? 1 : -1);
  sendTorqueCommand(torqueValue);
}

void motorPosition(float value) {
  targetPosition = value;
  sendPositionCommand(targetPosition);
}

// Serial communication functions
void sendTorqueCommand(float value) {
  arduino.write("T," + nf(value, 0, 2) + "\n");
}

void sendPositionCommand(float value) {
  arduino.write("P," + nf(value, 0, 2) + "\n");
}
