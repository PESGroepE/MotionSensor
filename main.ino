#include "MotionSensor.h"

const char* ssid = "pigroep5"; // Vervang door je WiFi SSID
const char* password = "pigroep5"; // Vervang door je WiFi wachtwoord
const char* serverAddress = "10.0.10.2"; // Vervang door het IP-adres of de hostname van je server
const int serverPort = 8080; // Poortnummer van de server

MotionSensor motionSensor;
WiFiClient client;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");

    motionSensor.initialisatie();
}

void loop() {
    motionSensor.startDetectie();
    motionSensor.stuurInformatie();
    delay(100);
    
    
}

void MotionSensor::stuurInformatie() {
    if (WiFi.status() == WL_CONNECTED) {
        if (client.connect("10.0.10.2", 8080)) {
                  String statusString = (motionSensor.status) ? "false" : "true";  // Gebruik de status variabele van de MotionSensor klasse
                  String request = "POST /motion/status?value=" + statusString + " HTTP/1.1\r\n";
                  request += "Host: " + String("10.0.10.2") + "\r\n";
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