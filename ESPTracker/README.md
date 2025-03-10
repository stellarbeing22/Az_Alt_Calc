# ESP8266 Blynk Integration

## Overview
This project integrates an ESP8266 with Blynk to display azimuth and altitude values received from a Python script. The ESP8266 reads serial data, extracts azimuth and altitude values, and sends them to the Blynk platform for real-time monitoring.

## Features
- Connects ESP8266 to a Wi-Fi network.
- Receives azimuth and altitude values over serial communication.
- Displays the received values on the Blynk app via virtual pins.
- Supports real-time monitoring through Blynk.

## Hardware Requirements
- ESP8266 D1 Mini (or any ESP8266-based board)
- Computer with Python script sending azimuth and altitude values
- Stable Wi-Fi connection

## Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software) (for flashing the ESP8266)
- ESP8266 Board Support Package
- [Blynk Library](https://github.com/blynkkk/blynk-library)
- Python environment (for the script sending data over serial)

## Wiring
Ensure the ESP8266 is properly connected to the serial communication source (e.g., a USB-to-serial module or another microcontroller sending data).

## Installation and Usage
1. **Set Up Blynk:**
   - Create a new project in the Blynk app.
   - Add two Value Display widgets (V0 for Azimuth and V1 for Altitude).
   - Note down your Blynk Authentication Token.

2. **Flash the ESP8266:**
   - Install required libraries in the Arduino IDE.
   - Update the `BLYNK_AUTH_TOKEN`, `ssid`, and `pass` values in the code.
   - Upload the sketch to the ESP8266.

3. **Run the Python Script:**
   - Ensure your Python script is sending azimuth and altitude values in the format `azimuth,altitude`.
   - The ESP8266 will read this data and send it to Blynk.

4. **Monitor on Blynk:**
   - Open the Blynk app and start the project.
   - View the real-time azimuth and altitude values on the app.

## Code Explanation
- Initializes Wi-Fi and connects to Blynk.
- Reads incoming serial data and extracts azimuth and altitude values.
- Sends these values to Blynk using virtual pins V0 and V1.
- Runs `Blynk.run()` continuously to maintain the connection.

## Future Improvements
- Add error handling for incorrect or missing serial data.
- Implement an automatic reconnect mechanism for Wi-Fi and Blynk.
- Expand functionality to store and analyze received data.

## License
This project is open-source and free to use under the MIT License.

## Acknowledgments
- [Blynk](https://blynk.io/) for providing an easy-to-use IoT platform.
- Open-source contributors for ESP8266 and Blynk libraries.

