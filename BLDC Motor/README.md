

## Overview

This folder contains sample code to operate BLDC (brushless) motors. The sample codes explores both open-loop torque control and position control.

## Hardware Requirements for BLDC motors
- Arduino board (compatible with SimpleFOC library)
- BLDC motor
- AS5600 magnetic sensor (or other position sensor)
- BLDC driver compatible with 3PWM control
- Power supply (9V)

## Pin Configuration
- PWM A: Pin 9
- PWM B: Pin 5
- PWM C: Pin 6
- Enable: Pin 8
- I2C for AS5600 sensor: Default I2C pins (SDA/SCL)

## Software Dependencies
### Arduino
- SimpleFOC library
  - Installation: Through Arduino Library Manager
  - Version: Latest stable release

### Processing
- ControlP5 library
  - Installation: Through Processing Contribution Manager
  - Version: Latest stable release
- Processing Serial library (included in Processing)

## Features
1. Open Loop Control
   - Adjustable torque intensity (-1 to 1)
   - Switchable rotation direction (CW/CCW)
   - Real-time feedback

2. Position Control
   - Precise positioning (0-359 degrees)
   - Direct angle input
   - Position feedback

## Installation
1. Arduino Setup
   ```
   1. Install the SimpleFOC library
   2. Upload the Arduino sketch to your board
   3. Verify serial connection (115200 baud rate)
   ```

2. Processing Setup
   ```
   1. Install the ControlP5 library
   2. Open the Processing sketch
   3. Adjust the serial port if needed (default is first available port)
   4. Run the sketch
   ```
## Serial Example - Communication Protocol
The Arduino and Processing sketches communicate via serial with the following commands:
- Torque Control: `T,value\n` (value range: -1 to 1)
- Position Control: `P,value\n` (value range: 0 to 359)