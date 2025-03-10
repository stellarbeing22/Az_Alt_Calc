# Stellarium ESP8266 Tracker

This project integrates Stellarium with an ESP8266 to receive and display real-time azimuth and altitude data of celestial objects via Blynk. The system consists of:
- A Python script that extracts azimuth and altitude data from Stellarium's web API.
- An ESP8266 program that receives this data and forwards it to Blynk.
- An experimental C program for learning conversions and calculations.

## Features
- Retrieves azimuth and altitude of a selected object from Stellarium.
- Sends data to an ESP8266 over a serial connection.
- Displays real-time data on a Blynk dashboard.

## Requirements
- Stellarium with the web API enabled (default: `http://localhost:8090`)
- Python 3 with `requests` and `pyserial`
- ESP8266 with the Blynk library
- A serial connection between the computer and ESP8266

## Setup
### 1. Stellarium Configuration
Enable the web API in Stellarium:
1. Open Stellarium.
2. Go to **Configuration Window** (F2) > **Plugins**.
3. Enable **Remote Control** and set it to `localhost:8090`.
4. Restart Stellarium.

### 2. Run the Python Script
```sh
pip install requests pyserial
python stellarium_tracker.py
```
The script retrieves azimuth and altitude data and sends it via serial to the ESP8266.

### 3. Flash the ESP8266
Upload `esp8266_blynk.ino` to the ESP8266:
1. Install the **Blynk** library in Arduino IDE.
2. Update the Wi-Fi credentials and Blynk Auth Token.
3. Flash the code to ESP8266.
4. Monitor serial output to confirm data reception.

### 4. Monitor Data in Blynk
- Open Blynk and add two **Value Displays** (V0 for azimuth, V1 for altitude).
- Run the project and observe real-time updates.

## File Structure
```
.
├── Stellarium_Fetch/            # Python script for Stellarium data extraction
│   ├── stellarium_Fetch.py
│   ├── README.md
├── ESPTracker/                  # ESP8266 Blynk integration
│   ├── ESPTracker.ino
│   ├── README.md
├── Alt_Az_Conversion/           # C code for calculations (learning purposes)
│   ├── Alt_Az_Conversion.c
│   ├── README.md
└── README.md                    # Project overview
```

## Acknowledgments
- [Original Python Code](<link-to-github>)
- Stellarium for providing real-time celestial data
- Blynk for IoT connectivity

## Future Improvements
- Automate telescope movement based on received data
- Integrate with a motor control system

This project was a great learning experience in serial communication, API integration, and ESP8266 programming!

