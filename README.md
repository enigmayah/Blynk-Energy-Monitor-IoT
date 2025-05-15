# Blynk Energy Monitor IoT

A compact IoT-based power and energy monitoring system using an ESP32 microcontroller, I2C-based LCD, and Blynk for real-time data visualization. The project includes an I2C scanner utility and a complete working model for monitoring voltage, current, power, and energy consumption (kWh).

## 🔧 Features

- **Real-time Power Monitoring** using ESP32 and EmonLib
- **Live Visualization on Blynk App**
- **LCD Display** via I2C for on-device feedback
- **EEPROM Logging** for persistent storage
- **WiFi Connectivity** for seamless remote access
- **I2C Address Scanner Utility**

## 📁 Contents

- `i2c_scanner.ino`: Utility code to scan and find I2C addresses of connected devices like the LCD.
- `energy_monitor_blynk.ino`: Main code for real-time voltage, current, and power monitoring with LCD display and Blynk integration.

## 📲 Blynk Setup

1. Use Blynk IoT (Blynk 2.0).
2. Set up a new template using your `TEMPLATE_NAME` and `TEMPLATE_ID`.
3. Replace the `BLYNK_AUTH_TOKEN`, `SSID`, and `PASS` in the main `.ino` file.
4. Assign Virtual Pins:
   - `V0` → Voltage (Vrms)
   - `V1` → Current (Irms)
   - `V2` → Power (W)
   - `V4` → Energy (kWh)

## ⚙️ Hardware Required

- ESP32 Dev Module
- I2C LCD 20x4
- Current sensor (e.g., CT sensor)
- Voltage divider/resistor network
- Internet access for ESP32
- Optional: EEPROM module (onboard)

## 🔌 Wiring Summary

- Voltage Sensor to GPIO 35  
- Current Sensor to GPIO 34  
- I2C LCD (SDA to GPIO 21, SCL to GPIO 22 by default)

## 🛠 Libraries Used

- [`EmonLib`](https://github.com/openenergymonitor/EmonLib)
- `LiquidCrystal_I2C`
- `Blynk` (ESP32)
- `Wire.h`
- `EEPROM.h`


### ⚡ Getting Started

1. Clone the repo:
   ```bash
   git clone https://github.com/your-username/SmartIoT-EnergyMonitor.git
   cd SmartIoT-EnergyMonitor
   Open .ino files with Arduino IDE or PlatformIO.
   Flash the code to ESP32.
   Monitor power data via LCD and Blynk.
