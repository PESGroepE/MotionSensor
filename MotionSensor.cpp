#include "MotionSensor.h" // Inclusie van de headerbestanden voor de MotionSensor klasse
/**
 * @brief Constructor voor de MotionSensor klasse.
 * 
 * @param serverAddr Het IP-adres of de hostname van de server.
 * @param serverPrt Het poortnummer van de server.
 */
MotionSensor::MotionSensor(const char* serverAddr, int serverPrt) 
: serverAddress(serverAddr), serverPort(serverPrt), status(true), timer(false) {}
/**
 * @brief Functie voor de initiële configuratie van de sensor.
 */
void MotionSensor::initialisatie() {
    pinMode(pirPin, INPUT); // Configureer PIR-sensor pin als input
    pinMode(ledPin, OUTPUT);  // Configureer LED-pin als output
    digitalWrite(pirPin, LOW);  // Stel PIR-sensor pin laag in
    digitalWrite(ledPin, HIGH); // Schakel LED uit

    Serial.print("Kalibreren van de sensor ");
    for (int i = 0; i < kalibratieTijd; i++) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println(" klaar");
    Serial.println("SENSOR ACTIEF");
    delay(1000);
}
/**
 * @brief Functie voor het starten van de bewegingsdetectie.
 */
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
/**
 * @brief Functie voor het verzenden van informatie naar de server.
 * 
 * @param client WiFiClient object voor het maken van de verbinding.
 */
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

