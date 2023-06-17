# Voice Controlled Car using Arduino

This code implements a voice-controlled car using an Arduino board. The car's movements are controlled by voice commands received through a Bluetooth module connected to the Arduino. The car is equipped with an ultrasonic sensor to detect obstacles and avoid collisions.

## Components Used

- Arduino board
- L298N Motor Driver
- HC-05 Bluetooth module
- Ultrasonic sensor (HC-SR04)
- Servo motor

## Libraries Used

The following libraries are required for this project:

- SoftwareSerial: Enables serial communication with the Bluetooth module.
- NewPing: Provides functions to interface with the ultrasonic sensor.
- Servo: Allows control of the servo motor.

## Pin Configuration

### L298N Motor Driver

- in1: Pin 5
- in2: Pin 6
- in3: Pin 9
- in4: Pin 10

### Servo Motor

- motor: Pin A4

### Ultrasonic Sensor

- Echo1: Pin A0
- Trig1: Pin A1
- Echo2: Pin A2
- Trig2: Pin A3

### L298N Enable Pins

- ENA: Pin 3
- ENB: Pin 11

## Setup

The `setup()` function performs the following tasks:

1. Initializes the serial communication with a baud rate of 9600.
2. Configures the input/output pins.
3. Attaches the servo motor and sets it to the starting position.
4. Sets the motor speed using the `setMotorSpeed()` function.

## Functionality

The main functionality of the code is implemented in the `loop()` function. Here's an overview of the different actions performed based on voice commands:

- Forward movement: `*forward`
- Backward movement: `*backward`
- Left turn: `*left`
- Right turn: `*right`
- Stop: `*control`
- Dance mode: `*dance` or `Dance`
- Circle mode: `*circle` or `Circle`
- Speed control: `*speed [speed value]`

The speed control commands allow adjusting the motor speed in the range of 10 to 100.

The code also includes functions for obstacle detection using the ultrasonic sensor. The `checkFrontObstacle()` and `checkRearObstacle()` functions stop the car if an obstacle is detected within a threshold distance.

## Notes

- Adjust the threshold distance in the `checkFrontObstacle()` and `checkRearObstacle()` functions according to your requirements.
- Ensure that the Bluetooth module is properly paired and connected to the Arduino.
- Modify the pin numbers in the code if you have connected the components to different pins.

Feel free to modify and enhance this code to suit your specific requirements for a voice-controlled car using Arduino.
