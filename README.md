# Arduino-Auto-Door-Lock-System

An Arduino-based electronic door lock system developed as a Digital Logic Design (DLD) project in 2026. The system uses a keypad for password entry, an LCD for user feedback, and a servo motor to control the lock mechanism.

## 📌 Project Overview

The Smart Auto Door Lock System is an embedded-systems prototype designed to demonstrate password-based access control using Arduino hardware.

The system checks the entered four-digit password. If the password is correct, the servo motor unlocks the door mechanism. If the password is incorrect, the system displays an access-denied message and activates an audible alarm.

## ✨ Features

- 🔑 Four-digit password authentication
- 🔄 Servo-controlled locking and unlocking
- 🖥️ 16×2 LCD status display
- 🚨 Buzzer alerts for password entry and denied access
- 🔴 Red LED for locked or denied-access indication
- 🟢 Green LED for successful access
- 🔁 Password change after successful authentication
- 🛡️ Temporary system lockout after three consecutive incorrect attempts
- 🎵 Startup sound and status animation

## 🧰 Hardware Components

- Arduino-compatible microcontroller
- 4×4 matrix keypad
- 16×2 LCD
- Servo motor
- Buzzer
- Red LED and green LED
- Current-limiting resistors
- Breadboard and jumper wires
- Suitable power supply
- Door-lock prototype or mechanical demonstration setup

## 💻 Software and Libraries

- Arduino C++
- Arduino IDE
- LiquidCrystal library
- Keypad library
- Servo library

## ⚙️ How It Works

1. The system initializes the LCD, LEDs, buzzer, and servo motor.
2. The LCD displays a startup animation and indicates that the system is ready.
3. The user enters a four-digit password using the keypad.
4. If the password is correct, the servo moves to the unlock position.
5. After successful authentication, the user can change the password or lock the door again.
6. If the password is incorrect, the LCD displays an access-denied message and the buzzer sounds an alarm.
7. After three incorrect attempts, the system activates a temporary lockout sequence.

## 🔌 Pin Configuration

| Component | Arduino Pin |
|---|---|
| LCD RS | 12 |
| LCD Enable | 11 |
| LCD D4 | 10 |
| LCD D5 | 9 |
| LCD D6 | 8 |
| LCD D7 | 7 |
| Servo signal | 6 |
| Keypad rows | 5, 4, 3, 2 |
| Keypad columns | A3, A2, A1, A0 |
| Buzzer | 13 |
| Green LED | A4 |
| Red LED | A5 |

**Note:** Verify your actual wiring before assembling the circuit. A4 and A5 are also I²C pins on common Arduino Uno boards, so avoid conflicting connections.

## 🚀 Getting Started

1. Install the Arduino IDE.
2. Install the LiquidCrystal, Keypad, and Servo libraries if they are not already available.
3. Connect the components according to the pin configuration and your verified circuit diagram.
4. Open `CODE.ino` in the Arduino IDE.
5. Select the correct Arduino board and port.
6. Compile and upload the program.
7. Enter the configured four-digit password to test the lock.

### Default Demonstration Password

The current source code uses `1234` as the initial password.

Change this value in the source code before demonstrating the project if required.

## 📸 Project Demonstration

Add your own project photos and circuit diagram here.

- Hardware setup
- Circuit diagram
- LCD startup screen
- Successful authentication
- Incorrect-password alert
- Servo locking and unlocking demonstration

## ⚠️ Limitations and Future Improvements

- Store password changes persistently so they survive a power cycle.
- Add a more robust lockout mechanism and recovery procedure.
- Improve password-change security.
- Add non-blocking timing to improve responsiveness.
- Consider a keypad timeout and input-cancellation feature.
- Test power requirements and mechanical reliability before real-world deployment.

This project is an educational prototype and should not be relied upon as the sole security mechanism for a real door.

## 🎓 Project Information

**Project:** Smart Arduino Auto Door Lock System  
**Domain:** Embedded Systems / Digital Logic Design  
**Year:** 2026


