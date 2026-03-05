# Low Voltage Overhead Conductor Break Detection System using IoT

## Overview

Low voltage AC distribution overhead lines are widely used in residential and rural power networks. These conductors can break due to aging, corrosion, storms, falling trees, or mechanical stress. When a live conductor falls to the ground, it may remain energized due to high earth resistance and low fault current. This condition can lead to serious electric shock hazards and accidental deaths.

This project presents a **cost-effective IoT-based monitoring system** that detects abnormal conditions in low voltage distribution lines. The system continuously monitors three-phase voltage and current using sensors connected to an ESP32 microcontroller. When a fault is detected, the system sends an alert using LoRa long-range wireless communication.

The proposed system is designed to improve **safety, reliability, and fault response time** in electrical distribution networks.

---

## Objectives

- Detect breakage of low voltage overhead conductors.
- Reduce electrocution risks in public areas.
- Monitor electrical parameters of distribution lines.
- Provide real-time alerts to maintenance teams.
- Develop a scalable and cost-effective monitoring system.

---

## Features

- Three phase voltage monitoring (R, Y, B phases)
- Current monitoring
- Conductor break detection
- Phase imbalance detection
- Low voltage detection
- Power outage detection
- Long-range communication using LoRa
- Battery backup monitoring
- Real-time alert transmission

---

## System Architecture

The monitoring device is installed on distribution poles. Voltage and current sensors measure electrical parameters continuously. The ESP32 microcontroller processes the data and determines whether the system is operating normally or if a fault has occurred.

If a fault condition is detected, the ESP32 transmits an alert message through LoRa communication to a remote monitoring station.

**System Flow**

Sensors → ESP32 Microcontroller → Fault Detection Algorithm → LoRa Communication → Monitoring Station

---

## Hardware Components

| Component | Description |
|--------|-------------|
| ESP32 | Microcontroller used for processing sensor data |
| ZMPT101B Voltage Sensor | Measures AC voltage of each phase |
| ACS712 Current Sensor | Measures line current |
| SX1278 LoRa Module | Long range wireless communication |
| SMPS Power Supply | Converts AC supply to low voltage DC |
| Rechargeable Battery | Provides backup power |
| Voltage Divider | Used for battery voltage monitoring |

---

## Pin Connections

### Voltage Sensors

| Phase | ESP32 Pin |
|------|-----------|
| R Phase | GPIO34 |
| Y Phase | GPIO35 |
| B Phase | GPIO32 |

### Current Sensor

| Sensor | ESP32 Pin |
|------|-----------|
| ACS712 | GPIO33 |

### Battery Monitoring

| Parameter | ESP32 Pin |
|---------|-----------|
| Battery Voltage | GPIO36 |

### LoRa Module

| LoRa Pin | ESP32 Pin |
|---------|-----------|
| MISO | 19 |
| MOSI | 23 |
| SCK | 18 |
| NSS | 5 |
| RST | 14 |
| DIO0 | 26 |

---

## Software Used

| Software | Purpose |
|--------|---------|
| Arduino IDE | Firmware development |
| ESP32 Board Package | Programming ESP32 |
| LoRa Library | LoRa communication |
| GitHub | Project hosting and documentation |

---

## Fault Detection Logic

The system identifies different fault conditions based on voltage and current values.

### Power Outage
All three phases have voltage below 50 V.

### Conductor Break
Voltage is present but current is approximately zero.

### Low Voltage
Phase voltage drops below 180 V.

### Phase Imbalance
Difference between phase voltages exceeds the allowed limit.

---

## Example LoRa Messages

### Normal Status

---

## Working Principle

1. Voltage and current sensors measure electrical parameters.
2. ESP32 reads the sensor values through analog inputs.
3. The microcontroller processes the data.
4. The system checks for abnormal conditions.
5. If a fault is detected, an alert message is generated.
6. The alert is transmitted via LoRa communication.
7. The monitoring station receives the alert for maintenance action.

---

## Applications

- Electrical distribution safety monitoring
- Smart grid infrastructure
- Rural power network monitoring
- Electrical utility maintenance systems
- Accident prevention systems

---

## Advantages

- Low cost compared to traditional monitoring systems
- Long range wireless communication
- Real-time fault detection
- Scalable for large distribution networks
- Improves public safety in power distribution systems

---

## Limitations

- Requires proper sensor calibration
- Environmental factors may influence sensor readings
- LoRa communication requires network coverage

---

## Future Improvements

- GPS-based fault location detection
- AI-based fault classification
- Mobile application for real-time monitoring
- Cloud-based data analytics
- Predictive maintenance using machine learning

---
