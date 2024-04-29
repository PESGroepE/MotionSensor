#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include "Arduino.h"

class MotionSensor {
public:
    MotionSensor();
    void initialisatie();
    void startDetectie();
    void stuurInformatie(); // Nieuwe lege functie
private:
    unsigned long laagTijd; // Tijd wanneer de sensoruitgang laag gaat
    boolean status;
    boolean timer;
};

#endif