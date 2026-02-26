<div align="center">

# ⏱️ Time-Stamped Temperature Data Logger
### ARM7 LPC2148 Based Real-Time Embedded Monitoring System

[![Language](https://img.shields.io/badge/Language-Embedded%20C-blue)]
[![Microcontroller](https://img.shields.io/badge/Microcontroller-LPC2148-orange)]
[![Architecture](https://img.shields.io/badge/Core-ARM7TDMI-green)]
[![Status](https://img.shields.io/badge/Project-Completed-brightgreen)]
[![Domain](https://img.shields.io/badge/Domain-Embedded%20Systems-red)]

</div>

---

## 📖 Project Overview

This project implements a **real-time temperature monitoring and logging system** using the **LPC2148 ARM7 microcontroller**.

The system continuously reads temperature from an **LM35 analog sensor**, timestamps the data using the **on-chip Real-Time Clock (RTC)**, and logs the information through **UART serial communication** for monitoring and analysis.

A **matrix keypad interface** allows users to configure system parameters such as time/date and temperature threshold, while a **16×2 LCD** provides live system feedback.

This project demonstrates full-stack embedded firmware development including:

- Peripheral register programming
- Real-time data acquisition
- Embedded UI design
- Communication protocols
- Fault detection logic

---

## 🚀 Key Features

✅ Real-time temperature measurement using ADC  
✅ Accurate timestamp generation via RTC  
✅ UART serial logging with INFO / ALERT messages  
✅ Configurable temperature threshold  
✅ User-editable RTC through keypad interface  
✅ Input validation (date, leap year handling)  
✅ LCD live monitoring display  
✅ LED alert for over-temperature condition  
✅ Menu-driven embedded user interface  
✅ Modular firmware architecture  

---

## 🧠 System Architecture
                    +----------------------+
                    |      LM35 Sensor     |
                    | (Analog Temperature) |
                    +----------+-----------+
                               |
                               | Analog Signal
                               v
                        +------+------+
                        |   ADC (MCU) |
                        +------+------+
                               |
                               v
+-------------+        +-------+--------+        +--------------+
|   Keypad    |------->|                |------->|    LCD 16x2   |
| (User Input)| GPIO   |    LPC2148     | GPIO   |  Display Unit |
+-------------+        |   ARM7 MCU     |        +--------------+
                       |                |
+-------------+        |                | UART TX/RX     +---------+
|   Switch    |------->|                |--------------->| MAX232  |
| Edit Mode   | GPIO   |                |                +----+----+
+-------------+        |                |                     |
                       |                |                     |
                       |                |                     v
                       |                |                 +--------+
                       |                |                 |   PC   |
                       |                |                 |Serial  |
                       |                |                 |Terminal|
                       |                |                 +--------+
                       |                |
                       |                |
                       |                | GPIO
                       |                +--------> LED / Buzzer
                       |                           Alert Output
                       |
                       | Internal Peripheral
                       +--------> RTC (Real Time Clock)
                                   Time & Date Source

---

## ⚙️ Hardware Components

| Component | Description |
|-----------|-------------|
LPC2148 | ARM7 Microcontroller |
LM35 | Analog Temperature Sensor |
16×2 LCD | Real-time display |
4×4 Matrix Keypad | User input |
LED | Alert indicator |
MAX232 | UART level converter |
Power Supply | 5V regulated |

---

## 💻 Software & Tools

- Embedded C
- Keil µVision IDE
- Flash Magic Programmer
- Serial Terminal (TeraTerm / RealTerm)
- Proteus (optional simulation)

---

## 🔄 System Workflow

### Initialization

- Configure system clock
- Initialize GPIO
- Start RTC
- Initialize ADC
- Configure UART
- Initialize LCD & Keypad

### Runtime Operation

1. Acquire temperature via ADC.
2. Read current time from RTC.
3. Display data on LCD.
4. Transmit log to PC via UART.
5. Compare temperature with threshold.
6. Trigger alert if limit exceeded.
7. Monitor keypad for configuration mode.

---

## 📟 Output Examples

### LCD Display
13:45:20 MON
13/05/25 T:32°C


### Serial Log
[INFO] Temp: 32.5°C @ 13:45:20 13/05/2025


### Alert Condition
[ALERT] Temp: 47.3°C @ 14:10:55 13/05/2025 - OVER TEMP!


---

## 🎛️ User Configuration

Users can modify:

- RTC Date & Time
- Temperature Threshold
- System Parameters

Navigation implemented using keypad with embedded **state-machine logic**.

---

## 🏗️ Firmware Architecture
Application Layer
├── Data Logging
├── Alert Management
├── Menu System
└── Control Logic

Driver Layer
├── ADC Driver
├── UART Driver
├── RTC Driver
├── LCD Driver
└── Keypad Driver

Hardware Layer
└── LPC2148 Peripherals

---

## 📂 Repository Structure
lpc2148-temperature-data-logger/
│── src/
│── include/
│── docs/
│── images/
│── README.md


---

## 🧪 Engineering Concepts Demonstrated

- ARM7 Peripheral Programming
- ADC Sensor Interfacing
- RTC Time Management
- UART Communication Protocols
- Embedded State Machines
- Real-Time Monitoring Systems
- Hardware-Software Integration
- Fault Detection Algorithms

---

## 🌍 Applications

- Industrial Temperature Monitoring
- Environmental Data Logging
- Medical Equipment Monitoring
- IoT Edge Devices
- Automation Systems

---

## 🔮 Future Enhancements

- SD Card Data Storage
- IoT Cloud Connectivity (WiFi / GSM)
- Mobile App Dashboard
- Multi-Sensor Support
- Low-Power Optimization

---

## 👨‍💻 Skills Demonstrated

This project highlights:

- Embedded C Programming
- ARM7 Architecture
- Peripheral Interfacing
- Real-Time System Design
- Debugging & Testing
- Communication Protocols
- Embedded UI Development

---

## 📸 Project Demonstration

images/
hardware_setup.jpg
lcd_output.jpg
serial_output.png


---

## 🎓 Learning Outcomes

- Designed complete embedded system from scratch
- Implemented real-time data acquisition pipeline
- Developed configurable embedded UI
- Integrated multiple peripherals successfully
- Built industrial-style monitoring solution

---

## ⭐ Author

**Syed Mohammed Muzzammil**  
Embedded Systems Engineer  

GitHub: https://github.com/muzzammil06  

---

## 📜 License

This project is intended for educational and demonstration purposes.

---

<div align="center">

⭐ If you found this project useful, please consider giving it a star!

</div>
