# Smart Parking Guidance System

A real-time parking slot monitoring system built with STM32F401CCU6 microcontroller that uses ultrasonic and IR sensors to detect vehicle presence and provides visual guidance through LCD display, LEDs, and buzzer alerts.

---

## Problem Statement

Parking management in urban areas faces critical challenges:

- **Time wastage** — Drivers spend several minutes searching for free slots
- **Traffic congestion** — Unnecessary vehicle movement inside lots increases jams and fuel consumption
- **Manual monitoring** — Requires human supervision, prone to errors
- **User inconvenience** — No clear indication of slot availability leads to frustration
- **Safety concerns** — Illegal parking or overcrowding may cause accidents and disputes

---

## Solution

A smart parking guidance system using the **STM32F401CCU6 microcontroller** that detects vehicle presence through ultrasonic and IR sensors, displays real-time slot availability on an LCD, provides visual feedback via LEDs, and alerts users through a buzzer when parking is full or wrong entry is detected. The system is designed for efficient monitoring, reduced congestion, and improved user convenience.

---

## System Architecture

### Core Controller
- **STM32F401CCU6** — Cortex-M4 microcontroller for processing and control

### Sensors (Input)
- **Ultrasonic Sensor (HC-SR04)** — Detects vehicle presence and measures distance
- **IR Sensors (×4)** — Monitors individual parking slots for occupancy

### Output Devices
- **LCD Display (16×2, I²C)** — Shows real-time distance and status information
- **LED Indicators (×7)** — Visual feedback for distance range and slot occupancy
  - 3 LEDs for ultrasonic (near, medium, far)
  - 4 LEDs for IR sensors (one per slot)
- **Buzzer** — Audio alert for very close proximity

### Communication & Debugging
- **UART to USB Module** — Debugging and serial monitoring

### Supporting Components
- Breadboard
- Jumper wires
- Micro-USB cable
- Resistors and capacitors

---

## Features

### Assignment Compliance (23CSE304)
- **Communication Interface (I²C)** — LCD communication via I²C protocol
- **Digital Interface** — Ultrasonic sensor echo pulse capture and IR sensor digital inputs
- **NVIC (Interrupts)** — IR sensors configured for interrupt-based detection
- **Display Interface** — 16×2 LCD display for status output and LED indicators

### Functional Features
- Real-time distance measurement (0–35 cm range)
- Three-level proximity detection (Very Near ≤10 cm, Medium ≤20 cm, Far ≤35 cm)
- Individual slot monitoring via 4 IR sensors
- Instant visual feedback through color-coded LEDs
- Audio alerts for critical proximity
- Serial monitoring for debugging

---

## Hardware Requirements

| Component | Quantity | Purpose |
|-----------|----------|---------|
| STM32F401CCU6 | 1 | Core processing unit |
| ST-Link V2 Debugger | 1 | Programming and debugging |
| HC-SR04 Ultrasonic Sensor | 1 | Distance measurement |
| IR Sensors | 4 | Slot occupancy detection |
| 16×2 LCD (I²C) | 1 | Status display |
| LEDs | 7 | Visual indicators |
| Buzzer | 1 | Audio alerts |
| UART-USB Module | 1 | Serial debugging |
| Breadboard | 1 | Circuit assembly |
| Jumper Wires | — | Connections |
| Resistors (220Ω, 10kΩ) | — | LED current limiting, pull-ups |

---

## Software & Tools

- **Keil µVision IDE** — Firmware development and compilation
- **STM32CubeMX** — Peripheral configuration
- **Serial Monitor** — Real-time debugging via UART

---

## Pin Configuration

### Ultrasonic Sensor
- Trigger Pin → GPIO (Output)
- Echo Pin → GPIO (Input, Timer Capture)

### IR Sensors
- IR Sensor 1–4 → GPIO (Input, Interrupt enabled)

### LEDs
- Ultrasonic LEDs (Near, Medium, Far) → GPIO (Output)
- IR LEDs (×4) → GPIO (Output)

### LCD Display
- I²C SDA → GPIO (I²C Data)
- I²C SCL → GPIO (I²C Clock)

### Buzzer
- Buzzer Pin → GPIO (Output)

---

## Working Principle

1. **Distance Detection** — Ultrasonic sensor continuously measures distance to incoming vehicles
2. **Proximity Classification** — System categorizes distance into three levels and activates corresponding LED
3. **Slot Monitoring** — Four IR sensors monitor individual parking slots independently
4. **Visual Feedback** — LCD displays distance and status; LEDs indicate slot occupancy
5. **Audio Alert** — Buzzer activates when vehicle is within 10 cm (Very Near)
6. **Serial Logging** — Real-time data sent via UART for monitoring and debugging

---

## System Operation

| Distance Range | LED Indicator | Buzzer | LCD Status |
|----------------|---------------|--------|------------|
| ≤ 10 cm | Near (ON) | Active | VERY NEAR |
| 11–20 cm | Medium (ON) | Off | MEDIUM |
| 21–35 cm | Far (ON) | Off | FAR |
| > 35 cm | All OFF | Off | CLEAR |

- **IR Sensor Detection** — When an IR sensor detects an obstacle (LOW signal), its corresponding LED turns ON

---

## Setup & Installation

### Hardware Setup
1. Connect ultrasonic sensor Trig and Echo pins to STM32 GPIO
2. Wire 4 IR sensors to GPIO inputs (interrupt-capable pins recommended)
3. Connect I²C LCD to STM32 I²C pins (SDA, SCL)
4. Attach LEDs with current-limiting resistors to designated GPIO outputs
5. Connect buzzer to GPIO output pin
6. Connect ST-Link V2 for programming

### Software Setup
1. Open project in Keil µVision IDE
2. Configure peripherals using STM32CubeMX (I²C, GPIO, Timers, NVIC)
3. Compile and flash firmware via ST-Link V2
4. Open serial monitor (9600 baud) for debugging

---

## Code Overview

```cpp
// Core functionality
- Ultrasonic pulse generation and echo measurement
- Distance calculation using time-of-flight
- Three-tier proximity classification
- IR sensor state polling
- I²C LCD communication
- LED and buzzer control
- UART serial logging
```

---

## Future Enhancements

- IoT integration (ESP8266/ESP32) for mobile app monitoring
- Cloud-based parking analytics
- Automated gate control
- Payment integration
- Multi-level parking support

---
