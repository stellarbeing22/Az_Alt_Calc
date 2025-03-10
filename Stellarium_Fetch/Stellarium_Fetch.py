import os
import time
import requests
import re
import threading
import serial.tools.list_ports #type = ignore

# Global variable to signal the thread to stop
stop_thread = False

# Global variable to store the Stellarium URL
stellarium_url = "http://localhost:8090/api/objects/info"

def clear_console():
    os.system('cls' if os.name == 'nt' else 'clear')

def extract_azimuth_altitude(content):
    # Use regular expression to extract azimuth and altitude
    match = re.search(r'Az\./Alt\.:.+?([\d.]+)°([\d.]+)\'([\d.]+)".+?([\d.]+)°([\d.]+)\'([\d.]+)"', content)
    if match:
        azimuth_deg, azimuth_min, azimuth_sec, altitude_deg, altitude_min, altitude_sec = map(float, match.groups())

        # Convert to decimal degrees
        azimuth = azimuth_deg + azimuth_min/60 + azimuth_sec/3600
        altitude = altitude_deg + altitude_min/60 + altitude_sec/3600

        return azimuth, altitude
    else:
        return None, None

def get_selected_object_info(ser=None):
    global stop_thread

    try:
        while not stop_thread:
            # Use the global stellarium_url variable
            url = stellarium_url
            response = requests.get(url)

            if response.status_code == 200:
                try:
                    # Explicitly set the encoding to 'utf-8'
                    response.encoding = 'utf-8'

                    # Extract azimuth and altitude using a simpler approach
                    content = response.text
                    start_index = content.find('Az./Alt.:')
                    end_index = content.find('</font>', start_index)
                    azimuth_altitude_text = content[start_index:end_index]

                    # Decode HTML entities
                    azimuth_altitude_text = re.sub(r'<.*?>', '', azimuth_altitude_text)

                    azimuth, altitude = extract_azimuth_altitude(azimuth_altitude_text)

                    if azimuth is not None and altitude is not None:
                        print(f"Azimuth: {azimuth}, Altitude: {altitude}")

                        # Send the azimuth and altitude to the Arduino through the serial port
                        if ser and ser.is_open:
                            ser.write(f"{azimuth},{altitude}\n".encode())
                            print(f"Sent data to Arduino: Azimuth={azimuth}, Altitude={altitude}")
                        else:
                            print("Serial port not open. Please establish communication port first.")
                    else:
                        print("Azimuth or altitude value is None.")
                except AttributeError as e:
                    print(f"Error parsing HTML: {e}")
                    print(f"Raw response: {response.text}")
            else:
                print(f"Failed to retrieve data. Status code: {response.status_code}")

            time.sleep(1)  # Adjust the delay as needed

    except requests.exceptions.RequestException as e:
        print(f"Error making request: {e}")

def list_available_com_ports():
    # Use pyserial's list_ports to get a list of available serial ports
    ports = serial.tools.list_ports.comports()

    print("Available COM Ports:")
    for i, port in enumerate(ports, start=1):
        print(f"{i}. {port.device}")
    
    selected_port_number = input("Enter the number of the COM port: ")
    
    try:
        selected_port_number = int(selected_port_number)
        if 1 <= selected_port_number <= len(ports):
            return ports[selected_port_number - 1].device
        else:
            print("Invalid COM port number.")
            return None
    except ValueError:
        print("Invalid input. Please enter a valid number.")
        return None

def establish_comm_port():
    # Add your code for establishing communication port here
    ser = None
    try:
        port_name = list_available_com_ports()
        if port_name:
            baud_rate = 9600  # Change the baud rate as needed

            ser = serial.Serial(port=port_name, baudrate=baud_rate, timeout=1)
            if ser.is_open:
                print(f"Communication port {port_name} established successfully.")
                return ser
            else:
                print(f"Failed to open communication port {port_name}.")
                return None
    except Exception as e:
        print(f"Error establishing communication port: {e}")
        return None

def update_stellarium_url():
    global stellarium_url
    new_url = input("Enter the new Stellarium URL: ")
    stellarium_url = new_url
    print("Stellarium URL updated successfully.")

def settings_menu():
    while True:
        clear_console()
        print("Settings:")
        print("1. Establish Communication Port")
        print("2. Update Stellarium URL")
        print("3. Back to Main Menu")

        choice = input("Enter your choice (1, 2, or 3): ")

        if choice == '1':
            # Establish communication port
            ser = establish_comm_port()
            if ser:
                stop_thread = False
                info_thread = threading.Thread(target=get_selected_object_info, args=(ser,))
                info_thread.start()

                # Wait for user input to stop the thread
                input("Press Enter to stop retrieving selected object info...")
                stop_thread = True
                info_thread.join()  # Wait for the thread to finish
                ser.close()  # Close the serial port when done
        elif choice == '2':
            # Update Stellarium URL
            update_stellarium_url()
        elif choice == '3':
            break
        else:
            print("Invalid choice. Please enter 1, 2, or 3.")

        input("Press Enter to continue...")

if __name__ == "__main__":
    while True:
        clear_console()
        print("Options:")
        print("1. Get Selected Object Info")
        print("2. Settings")
        print("3. Test Output (Print Altitude and Azimuth)")
        print("4. Exit")

        choice = input("Enter your choice (1, 2, 3, or 4): ")

        if choice == '1':
            # Start the thread for retrieving selected object info
            stop_thread = False
            info_thread = threading.Thread(target=get_selected_object_info, args=(None,))
            info_thread.start()

            # Wait for user input to stop the thread
            input("Press Enter to stop retrieving selected object info...")
            stop_thread = True
            info_thread.join()  # Wait for the thread to finish
        elif choice == '2':
            # Go to Settings menu
            settings_menu()
        elif choice == '3':
            # Test Output: Print Altitude and Azimuth to the console
            try:
                azimuth = 123.0  # Initial azimuth value (replace with actual data)
                altitude = 89.0  # Initial altitude value (replace with actual data)

                while True:
                    # Simulate changing values
                    azimuth += 0.1
                    altitude -= 0.1

                    print(f"Azimuth: {azimuth}, Altitude: {altitude}")
                    time.sleep(1)  # Adjust the delay as needed
            except KeyboardInterrupt:
                print("Test Output stopped by user.")
