# smart-home-energy-monitoring-and-contol-system
An IoT-based smart home energy monitoring and control system using ESP8266, ACS712 sensors, and relay modules to track real-time power consumption, detect phantom loads, identify abnormal energy usage, and automate appliance control.king and intelligent appliance control.
## Features
- Real-time energy monitoring
- Phantom load detection
- Fault detection for appliances
- Relay-based appliance control
- Optional motion-based automation
- ## Hardware Used
- ESP8266 (NodeMCU)
- ACS712 Current Sensor
- Relay Module
- Power Supply
- ## System Architecture
Appliance → ACS712 → Relay → ESP8266 → WiFi → Dashboard
## How It Works
The ACS712 sensor measures current drawn by appliances. The ESP8266 calculates power consumption and controls relays. The system detects energy inefficiencies and sends alerts.

