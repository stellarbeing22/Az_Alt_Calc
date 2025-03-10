#include <stdio.h>
#include <time.h>
#include<math.h>
// #include <unistd.h> 

#define latitude 31.25194
#define longitude 75.70388
#define RA  21.27180
#define Dec -19.87988
#define pi 3.14159265259


void FetchCurrTime(int * hour, int *minute, int *second, int *year, int *month, int *day); //Fetches the corrent time and date from the pc
void timeToUTC(int hour, int minute, int second,int *UTC_hour,int *UTC_minute,int offset_hour, int offset_minute);//Converts the fetchd date and time to UTC time by subtracting 5:30 
float timeToDec(int hour, int minute, int second); //can take both UTC and current time values to return the time in float
double JulianDate(int year, int month, int day, float UT); //Convert the date and decimal time to julian date
double calcGST(double JD); //Calculates Greenwitch Sidereal time
float GSTtoLST(float GST,float longt);//calculates local sidreal time 
float get_HA(float LST, float Ra);//calculates the hour angle 
float degToRad( float deg);//converts degrees to radians
float radToDeg(float rad);
double calcALT(float dec_r, float lat_r, float HA_r); //Calcualtes the Altitude from declination 
double calcAZ(float dec_r, float alt, float lat_r, float HA_r);// Calculate the Azimuth from Right Ascention 

int main() {

        int hour, minute, second,UTC_hour, UTC_minute; 
        int offset_hour = 5, offset_minute = 30;
        int year, month, day;
        
        FetchCurrTime(&hour, &minute, &second, &year, &month, &day);
        
        timeToUTC(hour, minute, second,&UTC_hour, &UTC_minute, offset_hour, offset_minute);
        
        float time = timeToDec(UTC_hour, UTC_minute, second);
        
        double JD = JulianDate(year, month, day, time);
        
        double GST = calcGST(JD); 
    
        float LST = GSTtoLST(GST, longitude); 
        int h = (int)LST;
        int m = (int)((LST - h) * 60);
        int s = (int)(((LST - h) * 60 - m) * 60);
        
        float HA = get_HA(LST, RA);

        float radHA = degToRad(HA*15);

        float ALT = calcALT(degToRad(Dec), degToRad(latitude), radHA);
        float AZ = calcAZ(degToRad(Dec),ALT,degToRad(latitude),radHA);
        /**/   
        printf("-----------------------------------------\n");
        printf("Local Time:      | %02d:%02d:%02d on %04d-%02d-%02d\n", hour, minute, second, year, month, day);
        printf("offset time:     | %d:%d:00                        \n", offset_hour, offset_minute);
        printf("UTC time :       | %d:%d:%d                        \n",UTC_hour, UTC_minute,second);
        printf("time in decimal: | %f                              \n", time);
        printf("Julian time:     | %.6f                            \n", JD);
        printf("GST:             | %.6f                            \n", GST);
        printf("LST:             | %02d:%02d:%02d                  \n", h, m, s);
        printf("HA:              | %f                              \n",HA);
        printf("HA(Rad):         | %f                              \n", radHA);
        printf("HA:              | %f                              \n", HA);
        printf("RA:              | %f                              \n", RA);
        printf("Dec:             | %f                              \n",Dec);
        printf("ALT:             | %f                              \n", ALT*180/pi);
        printf("AZ:              | %f                              \n",AZ*180/pi);
        printf("-----------------------------------------\n");

}
    
    //Functions
void FetchCurrTime(int * hour, int *minute, int *second, int *year, int *month, int *day){
    time_t raw_time;
    struct tm *time_info;
    
    // Get the current local time
    time(&raw_time);
    time_info = localtime(&raw_time); // Get local system time
    
    *year = time_info->tm_year + 1900;
    *month = time_info->tm_mon + 1;
    *day = time_info->tm_mday;
    *hour = time_info->tm_hour;
    *minute = time_info->tm_min;
    *second = time_info->tm_sec;
}

void timeToUTC(int hour, int minute, int second, int *UTC_hour, int *UTC_minute,int offset_hour, int offset_minute){
   
    //UTC time offset 
    *UTC_hour = hour - offset_hour;
    *UTC_minute = minute - offset_minute;
   

    //underflow handling
    if(*UTC_hour<0){
        *UTC_hour+=24;
    }

    if(*UTC_minute<0){
        *UTC_minute+=60;
        (*UTC_hour)--;
    }

    // Handle overflows (if needed)
    if (*UTC_minute >= 60) {
        *UTC_minute -= 60;
        (*UTC_hour)++;
    }

    if (*UTC_hour >= 24) {
        *UTC_hour -= 24;
    }
}

float timeToDec(int hour, int minute, int second){
    float time = hour + (minute/60.00) + (second/3600.00);
    return time;
}
/*
This was the older version of tje Julian date calcuaton 
double JulianDate(int year, int month, int day, float UT){
    float JD = 367*year - floor((7*(year + floor((month+9)/12)))/4) + floor(275*month/9) + day + 1721013.5 + UT/24;
    return JD;
}
*/

// Compute Julian Date (Fixed for Month Handling)
double JulianDate(int year, int month, int day, float UT) {
    if (month <= 2) {
        year--;
        month += 12;
    }
    
    int A = floor(year / 100);
    int B = 2 - A + floor(A / 4);  //Leap year correction

    double JD = floor(365.25 * (year + 4716)) + floor(30.6001 * (month + 1)) + day + B - 1524.5 + UT / 24.0;
    return JD;
}

double calcGST(double JD){
    double T = (JD - 2451545.0)/36525;
    double GST = 280.46061837 + 360.98564736629 * (JD - 2451545) + 0.000387933*T*T - (T*T*T)/38710000;
    GST = fmod(GST, 360.0);
    if (GST < 0) GST += 360.0;  //Ensure positive GST
    return GST/15;
}

float GSTtoLST(float GST, float longt) {
    float LST = GST + (longt / 15.0);  //Convert longitude to hours
    if (LST < 0.0) LST += 24.0;  // underflow
    if (LST >= 24.0) LST -= 24.0;  // overflow
    return LST;
}

float get_HA(float LST, float Ra){
    float HA = LST - Ra;
    if(HA<0) HA+=24;
    return HA; 
}

float degToRad(float deg){
    float rad = deg*pi/180;
    return rad;
}

float radToDeg(float rad){
    float deg = deg*180/pi;
    return deg;
}

double calcALT(float dec_r, float lat_r, float HA_r){
    double ALT = asin(sin(dec_r)*sin(lat_r) + cos(dec_r)*cos(lat_r)*cos(HA_r));
    return ALT;
}

double calcAZ(float dec_r, float alt, float lat_r, float HA_r){
    double AZ = acos((sin(dec_r)-sin(alt)*sin(lat_r))/(cos(alt)*cos(lat_r)));
    // Adjust for correct quadrant
    if (sin(HA_r) > 0) { 
        AZ = 2 * pi - AZ;  // Convert to 0°–360° range
    }
    return AZ;
}

