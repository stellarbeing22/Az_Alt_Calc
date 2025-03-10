#define BLYNK_TEMPLATE_ID "TMPL34NWvnmM2"  // Replace with your actual Template ID
#define BLYNK_TEMPLATE_NAME "Well"         // Replace with your Template Name
#define BLYNK_AUTH_TOKEN "F0xA7hS8mbjR9GXEy0VyOLKpGprOqMvT"  // Your Blynk Auth Token

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "WiFi";  
char pass[] = "adgj1357";  

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
}

void loop() {
    Blynk.run();

    if (Serial.available()) {
        String data = Serial.readStringUntil('\n'); // Read from Python
        data.trim();

        int commaIndex = data.indexOf(',');
        if (commaIndex > 0) {
            String azimuth = data.substring(0, commaIndex);
            String altitude = data.substring(commaIndex + 1);

            Serial.print("Az: "); Serial.println(azimuth);
            Serial.print("Alt: "); Serial.println(altitude);

            Blynk.virtualWrite(V0, azimuth);
            Blynk.virtualWrite(V1, altitude);
        }
    }
}
