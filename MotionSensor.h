#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include <ESP8266WiFi.h>
#include "Arduino.h"

class MotionSensor {
public:
    MotionSensor(const char* serverAddr, int serverPrt);
    void initialisatie();
    void startDetectie();
    void stuurInformatie(WiFiClient& client);
    bool getStatus() const { return status; }
    boolean status;
private:
    const char* serverAddress;
    int serverPort;
    bool previousStatus;
    unsigned long laagTijd; // Tijd wanneer de sensoruitgang laag gaat
    boolean timer;

    const int kalibratieTijd = 10; // Kalibratietijd voor de sensor
    const unsigned long pauze = 5000; // Tijd om aan te nemen dat beweging gestopt is
    const int pirPin = 5; // PIR sensor  pin
    const int ledPin = BUILTIN_LED; // LED pin
};

#endif