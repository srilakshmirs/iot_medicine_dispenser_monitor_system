# Setup Guide

This guide walks you through installing everything needed to build and run the IoT Based Smart Medicine Reminder and Monitoring System, from software setup to wiring and uploading code.

## 1. Install the Arduino IDE

Download and install the Arduino IDE (version 2.x recommended):
👉 https://www.arduino.cc/en/software

Available for Windows, macOS, and Linux.

## 2. Add ESP32 Board Support

The ESP32 isn't included by default in the Arduino IDE, so you need to add its board package.

1. Open Arduino IDE → **File → Preferences**
2. In "Additional Board Manager URLs", paste:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools → Board → Boards Manager**
4. Search for `esp32` and install the package by **Espressif Systems**
5. Once installed, select your board: **Tools → Board → ESP32 Arduino → ESP32 Dev Module**

Reference: https://github.com/espressif/arduino-esp32

## 3. Install Required Libraries

Go to **Sketch → Include Library → Manage Libraries**, and install the following:

| Library | Used For | Source |
|---|---|---|
| **Adafruit SSD1306** | OLED display driver | https://github.com/adafruit/Adafruit_SSD1306 |
| **Adafruit GFX Library** | Graphics primitives for OLED | https://github.com/adafruit/Adafruit-GFX-Library |
| **Servo** | Controls the SG90 servo motor (usually pre-installed with Arduino IDE) | https://www.arduino.cc/reference/en/libraries/servo/ |

Search each name in the Library Manager search bar and click **Install**.

## 4. Install USB Drivers (if needed)

- **ESP32 boards** typically use a CP2102 or CH340 USB-to-serial chip. If your board isn't detected:
  - CP2102 driver: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
  - CH340 driver: http://www.wch-ic.com/downloads/CH341SER_EXE.html
- **Arduino UNO** boards generally work out of the box on Windows 10/11, macOS, and Linux without extra drivers. On older Windows versions, install the standard Arduino driver bundled with the IDE.

## 5. Wiring

**ESP32:**
| Component | ESP32 Pin |
|---|---|
| OLED SDA | SDA (default I2C, usually GPIO 21) |
| OLED SCL | SCL (default I2C, usually GPIO 22) |
| Buzzer (+) | GPIO 26 |
| Push Button | GPIO 4 (other leg to GND, uses internal pull-up) |

**Arduino UNO:**
| Component | UNO Pin |
|---|---|
| Servo signal wire | D9 |
| Status LED | D13 (onboard LED can be used) |

Power both boards via USB or a power bank.

## 6. Upload the Code

1. Connect the **ESP32** via USB, select the correct **Port** under Tools → Port, and select **ESP32 Dev Module** as the board.
2. Open `esp32/sketch_esp32.ino` and click **Upload**.
3. Disconnect, then connect the **Arduino UNO**, select **Arduino Uno** as the board and its Port.
4. Open `arduino_uno/sketch_ard.ino` and click **Upload**.

> The two boards run independently — there's no direct wired communication between them, so they can be uploaded and powered separately.

## 7. Test the System

- OLED should show **"Medicine Reminder"** on boot.
- Every 5 minutes, the buzzer sounds and the OLED shows **"Time to take medicine!"**
- Press the push button to confirm — OLED should show **"Dose taken!"**
- The Arduino UNO's servo should rotate ~60° every 5 minutes, independent of the ESP32.

## Troubleshooting

| Issue | Fix |
|---|---|
| `SSD1306 allocation failed` in Serial Monitor | Check I2C wiring (SDA/SCL) and confirm the OLED's I2C address (commonly `0x3C`) |
| ESP32 not detected in Port list | Install CP2102/CH340 driver, try a different USB cable/port |
| Servo not moving | Check external power to the servo — USB power alone may be insufficient |
| Button not registering | Confirm wiring uses `INPUT_PULLUP` logic (button pulls pin to GND when pressed) |

## Reference Links

- Arduino millis() vs delay(): https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay
- ESP32 Technical Reference: https://www.espressif.com
- Arduino Servo Library Reference: https://www.arduino.cc/en/reference/servo
