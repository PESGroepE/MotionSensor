#include "MotionSensor.h"

MotionSensor::MotionSensor(const char* serverAddr, int serverPrt) 
: serverAddress(serverAddr), serverPort(serverPrt), status(true) {}

void MotionSensor::initialisatie() {
    pinMode(pirPin, INPUT);
    pinMode(ledPin, OUTPUT);
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

void MotionSensor::startDetectie(WiFiClient& client) {
    status = digitalRead(pirPin);
    if (status == HIGH) {
      delay(1000);
      status = digitalRead(pirPin);
      if (status == HIGH) {
        oldstatus = true;
      }
    }
    Serial.println(status);

}

void MotionSensor::stuurInformatie(WiFiClient& client) {
    if (WiFi.status() == WL_CONNECTED) {
        if (client.connect(serverAddress, serverPort)) {
                  String statusString = (this->status) ? "false" : "true";  // Gebruik de status variabele van de MotionSensor klasse
                  String request = "POST /motion/status?value=" + statusString + " HTTP/1.1\r\n";
                  request += "Host: " + String(serverAddress) + "\r\n";
                  request += "Connection: close\r\n\r\n";
                  client.print(request);
                  client.stop();  // Sluit de verbinding direct na het versturen van het verzoek
        } else {
            Serial.println("Connection to server failed");
        }
    } else {
        Serial.println("WiFi not connected");
    }

}

