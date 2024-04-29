#include "MotionSensor.h"
#include "ConstantsMotionSensor.h"

MotionSensor::MotionSensor() : status(true), timer(false) {}

void MotionSensor::initialisatie() {
    Serial.begin(9600);
    pinMode(pirPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(pirPin, LOW);
    digitalWrite(ledPin, HIGH);

    Serial.print("Kalibreren van de sensor ");
    for (int i = 0; i < kalibratieTijd; i++) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" klaar");
    Serial.println("SENSOR ACTIEF");
    delay(1000);
}

void MotionSensor::startDetectie() {
    if (digitalRead(pirPin) == HIGH) {
        if (status) {
            digitalWrite(ledPin, LOW);
            Serial.println("---\nBeweging gedetecteerd, Status: " + String(status));
            status = false;
            delay(50);
        }
        timer = true;
    }

    if (digitalRead(pirPin) == LOW) {
        if (timer) {
            laagTijd = millis();
            timer = false;
        }

        if (!status && millis() - laagTijd > pauze) {
            digitalWrite(ledPin, HIGH);
            Serial.println("---\nBeweging gestopt, Status: " + String(status));
            status = true;
            delay(50);
        }
    }
}

void MotionSensor::stuurInformatie() {
    // Hier komt code om status te sturen naar de pi of om het opteslaan in op de http server van de wemos?
}