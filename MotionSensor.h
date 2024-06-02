#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include <ESP8266WiFi.h>
#include "Arduino.h"

class MotionSensor {
public:
    MotionSensor(const char* serverAddr, int serverPrt);
    void initialisatie();
    void startDetectie(WiFiClient& client);
    void stuurInformatie(WiFiClient& client);
    bool getStatus() const { return status; }
    boolean status;
private:
    const char* serverAddress;
    int serverPort;

    int oldstatus;

    const int kalibratieTijd = 10; // Kalibratietijd voor de sensor
    const int pirPin = 5; // PIR sensor  pin
    const int ledPin = BUILTIN_LED; // LED pin
};

#endif