# 🚀 Digital Security Passcode System - ATmega32

![Embedded Systems](https://img.shields.io/badge/Embedded-Systems-blue.svg) ![ATmega32](https://img.shields.io/badge/MCU-ATmega32-orange.svg) ![C](https://img.shields.io/badge/Language-C-green.svg)

> **Industrial-Grade Digital Security Passcode System designed around the ATmega32 microcontroller.**

## 📋 Table of Contents
- [Project Overview](#-project-overview)
- [System Architecture](#-system-architecture)
- [Hardware Interfacing](#-hardware-interfacing)
- [Software Implementation](#-software-implementation)
- [Getting Started](#-getting-started)
- [Team Information](#-team-information)

## 📖 Project Overview
This project implements a complete digital security passcode access system. It is built strictly following a professional 4-Layer Architecture (LIB, MCAL, HAL, APP) to ensure modularity, scalability, and hardware abstraction.

### Key Features
*   **Default Master Passcode:** `1234` (4-digit length).
*   **Success Feedback:** Lights up the Green LED and displays "ACCESS GRANTED" on the Character LCD.
*   **Failure Feedback:** Lights up the Red LED and displays "ACCESS DENIED".
*   **Security Lockout System:** Triggers an Active Buzzer alarm and completely locks the system for 10 seconds after 3 consecutive failed attempts.

## 🏗️ System Architecture
The software is organized into four distinct layers:

1.  **LIB (Libraries):** Standard data types and bit manipulation macros (`STD_TYPES.h`, `BIT_MATH.h`).
2.  **MCAL (Microcontroller Abstraction Layer):** Drivers for ATmega32 internal peripherals (e.g., DIO driver).
3.  **HAL (Hardware Abstraction Layer):** Drivers for external components (LCD and Matrix Keypad).
4.  **APP (Application Layer):** The core business logic tying everything together (`main.c`).

## 🔌 Hardware Interfacing (Proteus Map)
The physical components are distributed across the ATmega32 ports as follows:

| Component | ATmega32 Port / Pins | Functional Description |
| :--- | :--- | :--- |
| **Character LCD (16x2)** | `PORTA` (RS=PA1, EN=PA2, Data=PA4-PA7) | 4-bit mode visual user interface. |
| **Matrix Keypad (4x4)** | `PORTC` (Pins 0 to 7) | Matrix input for passcode entry (requires internal pull-ups for inputs). |
| **Green LED** | `PORTB`, Pin 0 (`PB0`) | Indicates successful authentication (Access Granted). |
| **Red LED** | `PORTB`, Pin 1 (`PB1`) | Indicates incorrect password entry (Access Denied). |
| **Active Buzzer** | `PORTB`, Pin 2 (`PB2`) | Audible security alarm for the 3-strike lockout. |

## 💻 Software Implementation

### Clock Configuration
The system operates at a clock frequency of **8 MHz**. The macro `F_CPU` is defined in `main.c` to prevent build warnings and ensure accurate timing for the `_delay_ms()` function:
```c
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
```

### Complete Source Code Flow
1.  **Initialization:** The system configures the DIO pins for LEDs and the buzzer as outputs, setting their initial state to LOW. It then initializes the LCD and Keypad modules.
2.  **Passcode Entry:** The LCD prompts the user. As keys are pressed on the keypad, they are captured, and a '*' is displayed for each digit.
3.  **Validation:** Upon receiving 4 digits, the system compares the input against the `MASTER_PASSCODE`.
4.  **Feedback & Lockout:** Based on the comparison, it either grants access (Green LED) or denies it (Red LED). If failures reach 3, the system locks up (Buzzer ON) for 10 seconds.

*(Full source codes including `STD_TYPES.h`, `BIT_MATH.h`, `DIO`, `LCD`, `KEYPAD`, and `main.c` are included in the repository).*

## 🚀 Getting Started

### Prerequisites
*   **Microchip Studio (AVR Studio):** To compile the C code and generate the `.hex` file.
*   **Proteus Professional:** To run the hardware simulation.
*   **Git:** For version control.

### How to Run
1.  Clone this repository to your local machine.
2.  Open the project in Microchip Studio and build the solution (ensure target MCU is ATmega32).
3.  Open the provided Proteus simulation file.
4.  Double-click the ATmega32 microcontroller in Proteus, load the generated `.hex` file, and set the clock frequency to `8MHz`.
5.  Run the simulation and test the passcode system!

## 👥 Team Information

*   **Instructor:** Eng. Ahmed Diaa Lashin
*   **Target MCU:** ATmega32 (8-bit AVR)
