# ATmega32 Peripheral & Module Drivers

A collection of peripheral and module drivers developed for the AVR ATmega32 microcontroller and various hardware components, built and used across multiple embedded systems projects.

---

## Table of Contents

- [Overview](#overview)
- [Driver List](#driver-list)
---

## Overview

All drivers follow a layered architecture model separating MCAL (Microcontroller Abstraction Layer) and HAL (Hardware Abstraction Layer) concerns. Each driver is self-contained with its own `.c` and `.h` files, configurable via header macros or configuration structs.

---

## Driver List

### MCAL — Microcontroller Abstraction Layer

| Driver | Description |
|--------|-------------|
| GPIO | General-purpose I/O pin direction and read/write control |
| ADC | Analog-to-Digital Converter with configurable reference voltage and prescaler |
| TIMER (0, 1, 2) | Timer driver supporting Normal and CTC modes with dynamic configuration and callback support |
| ICU | Input Capture Unit for pulse width and frequency measurement |
| UART | Serial communication driver with configurable baud rate, parity, stop bits, and data bits |
| SPI | Serial Peripheral Interface for master/slave communication |
| I2C | Two-wire serial communication for interfacing with external devices |

### HAL — Hardware Abstraction Layer

| Driver | Description |
|--------|-------------|
| LCD | 16x2 LCD driver supporting 4-bit and 8-bit modes |
| Keypad | 4x4 matrix keypad scanning driver |
| LED | LED control driver with positive and negative logic support |
| DC Motor | Motor direction and speed control via H-Bridge and PWM |
| Ultrasonic Sensor | HC-SR04 distance measurement using ICU |
| Multiple Ultrasonics | Multi-sensor ultrasonic distance measurement |
| LM35 Sensor | Temperature reading via ADC channel |
| Flame Sensor | Digital flame detection with configurable pin |
| EEPROM | External 24Cxx EEPROM read/write via I2C |
| Alarm / Buzzer | Active buzzer control driver |


