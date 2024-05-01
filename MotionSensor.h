#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include <ESP8266WiFi.h>
#include "ConstantsMotionSensor.h"
#include "Arduino.h"

class MotionSensor {
public:
    MotionSensor(const char* serverAddr, int serverPrt);
    void initialisatie();
    void startDetectie();
    void stuurInformatie(WiFiClient& client);
    boolean status;
private:
    const char* serverAddress;
    int serverPort;
    unsigned long laagTijd; // Tijd wanneer de sensoruitgang laag gaat
    boolean timer;
};

#endif