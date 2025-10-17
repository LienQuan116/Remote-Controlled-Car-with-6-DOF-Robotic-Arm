# Design Objective:
Develop a remote-controlled vehicle integrated with a 6-DOF robotic arm and a camera for exploration and surveillance applications.
# Hardware Components:
Arduino Uno R3 – main controller for vehicle movement
ESP32 – controls the robotic arm and camera module
NRF24L01 – wireless RF communication between controller and vehicle
L298N Motor Driver – controls four DC motors
Mecanum Wheels – enable omnidirectional movement
Servo Motors (MG90S, MG996R) – control six arm joints
ESP32-CAM / IP Camera – real-time video transmission
18650 Batteries, TP4056 Charger, LM7805/LM7812 Regulators – power supply
# Software Tools:
Arduino IDE – coding and uploading control programs
MIT App Inventor – Android app for Bluetooth robotic arm control
Altium Designer – schematic and PCB design
# Control System Overview:
Remote controller sends movement commands via NRF24L01.
Vehicle receives data and controls DC motors for movement.
Mobile app communicates with ESP32 through Bluetooth to control the robotic arm.
Camera streams real-time video to the user’s device for better observation.
# System Features:
Smooth omnidirectional motion using Mecanum wheels.
6-DOF robotic arm capable of grabbing and lifting small objects.
Real-time video feedback from onboard camera.
Wireless communication with low latency.
# Power System:
Powered by 4×18650 Li-ion batteries.
TP4056 charging module for safe recharging.
LM7812 and LM7805 regulators for stable 12V and 5V outputs.
# Results:
Stable movement and responsive control.
Functional robotic arm with 6 servo motors.
Real-time camera monitoring enhances precision and usability.
