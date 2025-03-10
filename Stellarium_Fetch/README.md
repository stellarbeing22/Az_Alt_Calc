# Alt-Az Yoinker for ESP8266 and Blynk

This project integrates the **Alt-Az Yoinker** with an **ESP8266** to retrieve azimuth and altitude data from **Stellarium**, then sends it to the **Blynk** server for remote monitoring.

## Overview

- Uses a Python script to fetch celestial object coordinates (Azimuth & Altitude) from Stellarium.
- Transfers the data via **Serial Communication** to an **ESP8266**.
- The ESP8266 forwards the data to **Blynk**, allowing real-time remote monitoring.

## Features

- Automated retrieval of **Alt-Az coordinates**.
- Serial communication between **Python & ESP8266**.
- Live updates on **Blynk Dashboard**.

## Hardware Requirements

- **ESP8266 (D1 Mini, NodeMCU, etc.)**
- Computer running **Stellarium**
- USB cable for serial communication
- Internet connectivity (for Blynk)

## Software Requirements

- **Stellarium** (Running with web API enabled)
- **Python 3** (with `requests`, `serial` modules installed)
- **Arduino IDE** (or PlatformIO) for ESP8266
- **Blynk Library** for ESP8266

## Installation & Setup

### 1. Install Required Python Libraries
```bash
pip install requests pyserial
```

### 2. Enable Stellarium Web API
- Open Stellarium.
- Enable remote API at `http://localhost:8090/api/objects/info`.

### 3. Flash ESP8266 with Blynk Code
- Modify `BLYNK_AUTH_TOKEN`, `ssid`, and `pass` in the ESP8266 script.
- Upload the script to ESP8266 using Arduino IDE.

### 4. Run Python Script
```bash
python alt_az_yoinker.py
```

### 5. Monitor Data on Blynk
- Open **Blynk App**.
- Add two virtual pins (V0 for Azimuth, V1 for Altitude).
- Observe real-time data updates.

## Usage

1. Run Stellarium.
2. Execute the Python script.
3. Ensure ESP8266 is connected to WiFi & Blynk.
4. Monitor **Azimuth** & **Altitude** on Blynk.

## Acknowledgment

This project is based on the **Alt-Az Yoinker** by [Onvett](https://github.com/Onvett/Alt-Az-Yoinker/tree/main) with modifications for ESP8266 and Blynk.

## License

This project follows the original repository's license. Check [Onvett's repository](https://github.com/Onvett/Alt-Az-Yoinker/tree/main) for details.

