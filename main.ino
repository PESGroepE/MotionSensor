#include "MotionSensor.h"

MotionSensor motionSensor;

void setup() {
    motionSensor.initialisatie();
}

void loop() {
    motionSensor.startDetectie();
    
}