# ⏱ Time-Stamped Temperature Data Logger (LPC2148)

## 📌 Overview
This project implements a real-time temperature monitoring and logging system using the **LPC2148 ARM7 microcontroller**. The system reads temperature data from an **LM35 sensor**, timestamps it using the built-in **RTC (Real-Time Clock)**, and logs the information via **UART serial communication**.

Users can configure RTC parameters and temperature set-points through a **matrix keypad interface**, while a **16×2 LCD** provides live system feedback.

The project demonstrates integration of multiple embedded peripherals including **ADC, RTC, UART, GPIO, and external user interfaces**.

---

## 🚀 Key Features
- 🌡 Real-time temperature measurement using LM35 sensor and ADC
- 🕒 Accurate timestamping using LPC2148 RTC
- 📟 UART serial logging with **INFO** and **ALERT** messages
- ⌨ User configuration via matrix keypad (RTC & temperature set-point)
- 📅 Leap year and date validation logic
- ⬅ Backspace and confirm support for numeric input
- 📺 16×2 LCD for live temperature and time display
- 🔴 LED indication for over-temperature condition
- ⚠ Automatic alert generation when threshold is exceeded

---

## 🛠 Hardware Components
- LPC2148 ARM7 Microcontroller
- LM35 Temperature Sensor
- 16×2 Character LCD
- 4×4 Matrix Keypad
- LEDs (Status / Alert indication)
- UART Interface (Serial Communication)

---

## 💻 Software & Development Tools
- Embedded C
- Keil µVision IDE
- Flash Magic (for programming)
- Proteus (optional simulation)

---

## ⚙ System Operation
1. The LM35 sensor measures ambient temperature.
2. LPC2148 ADC converts the analog signal to digital data.
3. RTC provides current date and time.
4. Temperature and timestamp are displayed on the LCD.
5. Data is transmitted through UART for logging.
6. If temperature exceeds the configured set-point:
   - ALERT message is sent via UART  
   - LED indicator is activated  

Users can enter **Edit Mode** using the keypad to:
- Modify RTC date and time
- Change temperature threshold value

---

## 🎯 Learning Outcomes
This project demonstrates:

- ARM7 peripheral programming
- ADC sensor interfacing
- RTC configuration and time management
- UART communication protocols
- Embedded user interface design
- Input validation and state-machine logic

---

## 📸 Future Improvements
- SD card data logging
- PC visualization dashboard
- IoT cloud integration
- Buzzer alarm system

---

## 👨‍💻 Author
**Syed Mohammed Muzzammil**  
Embedded Systems Enthusiast
