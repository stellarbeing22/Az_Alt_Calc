# Astronomical Position Calculator

## Overview
This project calculates the local altitude and azimuth of a celestial object using astronomical formulas. The program fetches the current system time, converts it to UTC, calculates the Julian Date, Greenwhich Sidereal Time (GST), Local Sidereal Time (LST), Hour Angle (HA), and finally determines the altitude and azimuth of the given celestial coordinates.

## Features
- Fetches the current date and time from the system.
- Converts local time to UTC.
- Computes the Julian Date.
- Calculates the Greenwich Sidereal Time (GST) and Local Sidereal Time (LST).
- Determines the Hour Angle (HA) of the celestial object.
- Computes the Altitude (ALT) and Azimuth (AZ) based on observer's location.
- Outputs all relevant calculations in a formatted manner.

## Requirements
- A C compiler (GCC recommended)
- Standard C libraries (stdio.h, time.h, math.h)

## Compilation and Execution
To compile the code, use:
```sh
gcc Alt_Az_Conversion.c -o Alt_Az_Conversion -lm
```
To run the program:
```sh
./Alt_Az_Conversion
```

## Formulae Used
1. **Julian Date (JD)**:
   ```
   JD = 367*year - floor((7*(year + floor((month+9)/12)))/4) + floor(275*month/9) + day + 1721013.5 + UT/24
   ```

2. **Greenwich Sidereal Time (GST)**:
   ```
   GST = 280.46061837 + 360.98564736629 * (JD - 2451545) + 0.000387933*T*T - (T*T*T)/38710000;
   ```

3. **Local Sidereal Time (LST)**:
   ```
   LST = GST + (Longitude / 15.0);
   ```

4. **Hour Angle (HA)**:
   ```
   HA = LST - RightAscension;
   ```

5. **Altitude (ALT)**:
   ```
   ALT = asin(sin(Dec) * sin(Lat) + cos(Dec) * cos(Lat) * cos(HA));
   ```

6. **Azimuth (AZ)**:
   ```
   AZ = acos((sin(Dec) - sin(ALT) * sin(Lat)) / (cos(ALT) * cos(Lat)));
   ```
   If `sin(HA) > 0`, then:
   ```
   AZ = 2 * π - AZ;
   ```

## Example Output
```
-----------------------------------------
Local Time:      | 14:30:15 on 2025-03-10
offset time:     | 5:30:00                        
UTC time :       | 8:00:15                        
time in decimal: | 8.004167                      
Julian time:     | 2460365.833333                 
GST:             | 14.567890                      
LST:             | 15:23:45                       
HA:              | 2.567                          
HA(Rad):         | 0.448                          
RA:              | 21.27180                       
Dec:             | -19.87988                      
ALT:             | 45.32                          
AZ:              | 128.54                         
-----------------------------------------
```

## Configuration
To modify the observer’s location, update the following values in the code:
```c
#define latitude 31.25194
#define longitude 75.70388
```
To change the celestial object’s coordinates, update:
```c
#define RA 21.27180
#define Dec -19.87988
```

## Future Improvements
- Allow user input for observer’s location and celestial coordinates.
- Support for multiple celestial objects.
- Graphical interface for visualization.

## License
This project is open-source.

