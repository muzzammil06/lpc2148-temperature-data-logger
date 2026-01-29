# Time-Stamped Temperature Data Logger (LPC2148)

## 📌 Project Overview
This project implements an embedded temperature monitoring and data logging system using the LPC2148 ARM7 microcontroller. The system measures temperature using an LM35 sensor, timestamps data using RTC, and logs information via UART. Users can edit RTC parameters and temperature set-points using a matrix keypad.

## 🔧 Features
- Real-time temperature measurement using LM35
- RTC-based date and time stamping
- UART serial logging with INFO and ALERT messages
- Keypad-based edit mode for RTC and temperature set-point
- Leap year and month-day validation
- Backspace and confirm support for numeric input
- 16×2 LCD for real-time display
- LED indication for over-temperature condition

## 🛠 Hardware Used
- LPC2148 ARM7 Microcontroller
- LM35 Temperature Sensor
- 16×2 LCD
- Matrix Keypad
- LEDs
- UART (Serial Communication)

## 💻 Software & Tools
- Embedded C
- Keil µVision IDE
- (Optional) Proteus for simulation

## 📂 Project Structure

## ▶ How It Works
- Temperature is sampled using ADC
- RTC provides time and date
- Data is displayed on LCD
- UART logs temperature with timestamps
- Alerts are generated when temperature exceeds set-point

## 👤 Author
Syed Mohammed Muzzammil  
Embedded Systems Enthusia

