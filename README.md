# IoT Based Smart Medicine Reminder and Monitoring System

An IoT-based medication reminder and dispenser simulation built using an **ESP32** and an **Arduino UNO**. The system reminds users to take their medicine through a buzzer and OLED display, lets them confirm the dose with a push-button, and simulates dispensing using a servo-motor-driven rotating mechanism — all without needing internet or a real-time clock.

> Final year BCA (IoT) project 

## Overview

Missing medication doses is a common problem, especially for elderly patients and those with chronic conditions. This project automates the reminder process and simulates automatic dispensing, while remaining low-cost, offline, and easy to use.

The system uses **two independent microcontrollers**:

- **ESP32** — handles all user interaction: OLED display messages, buzzer alerts, and push-button confirmation.
- **Arduino UNO** — independently rotates a servo motor every 5 minutes to simulate pill dispensing.

Both boards run on their own non-blocking `millis()` timers and don't need to communicate with each other, which keeps the design simple and fault-tolerant.

## Features

- ⏰ Automatic medicine reminders every 5 minutes (buzzer + OLED)
- 🔘 Dose confirmation via push-button
- 🔁 Second reminder retry if the dose isn't confirmed
- ⚙️ Simulated dispensing using a servo-driven rotating fan mechanism
- 🔌 Fully offline — no Wi-Fi, app, or internet required

## Hardware Used

| Component | Purpose |
|---|---|
| ESP32 Dev Module | User interface — display, buzzer, button |
| Arduino UNO | Servo motor control (dispensing) |
| SG90 Servo Motor | Rotates the dispenser mechanism |
| OLED Display (128x64, I2C) | Shows reminder / confirmation messages |
| Buzzer | Audio alert |
| Push Button | Dose confirmation input |
| Breadboard + Jumper Wires | Wiring |
| Power Bank / USB cable | Power supply |

## Software / Libraries

- [Arduino IDE](https://www.arduino.cc/en/software)
- [ESP32 Board Package](https://github.com/espressif/arduino-esp32)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)
- Arduino built-in `Servo.h` library

See [SETUP.md](./SETUP.md) for detailed installation and setup steps.

## How It Works

1. Every 5 minutes, the ESP32 triggers a buzzer + OLED alert: **"Time to take medicine!"**
2. The user presses the push button to confirm the dose. The display updates to **"Dose taken!"**
3. If no confirmation is received, a second reminder is triggered after 1 minute.
4. Independently, the Arduino UNO rotates the SG90 servo motor by 60° every 5 minutes, simulating the release of one dose from the dispenser.

Since the two boards run on separate timers, there's no direct communication link between them — this keeps the design simple and avoids synchronization failures.

## Pin Connections

**ESP32**
| Pin | Component |
|---|---|
| GPIO 26 | Buzzer |
| GPIO 4 | Push Button (INPUT_PULLUP) |
| SDA / SCL (default I2C pins) | OLED Display |

**Arduino UNO**
| Pin | Component |
|---|---|
| D9 | Servo signal |
| D13 | Status LED |

## Project Structure

```
├── esp32/
│   └── sketch_esp32.ino     # ESP32 code — display, buzzer, button
├── arduino_uno/
│   └── sketch_ard.ino       # Arduino UNO code — servo control
├── README.md
└── SETUP.md
```

> These are the final, working versions of the firmware. Earlier drafts explored a single-board design and a wired-signal handoff between the two boards, but the versions above use fully independent timers on each board, matching the final design described in this README.

## Future Enhancements

- Cloud connectivity for dose logging and caregiver alerts (using ESP32 Wi-Fi)
- Companion mobile app
- RTC module for accurate real-world time tracking
- Voice-based reminders
- Battery backup for power-cut resilience
- Multi-dose / multi-user scheduling
- Sensor-based confirmation (load cell / IR) instead of a button
