#ifndef MOTIONSENSOR_H
#define MOTIONSENSOR_H

#include <ESP8266WiFi.h>  // Inclusie van de headerbestanden voor de ESP8266 WiFi-bibliotheek
#include "Arduino.h"  // Inclusie van de headerbestanden voor Arduino functies
/**
 * @brief De MotionSensor klasse biedt functionaliteit voor het detecteren van beweging en het verzenden van informatie naar een server.
 */
class MotionSensor {
public:
    /**
     * @brief Constructor voor de MotionSensor klasse.
     * 
     * @param serverAddr Het IP-adres of de hostname van de server.
     * @param serverPrt Het poortnummer van de server.
     */
    MotionSensor(const char*, int, int, int, int);

    /**
     * @brief Functie voor de initiële configuratie van de sensor.
     */
    void initialisatie();

    /**
     * @brief Functie voor het starten van de bewegingsdetectie.
     */
    void startDetectie();

    /**
     * @brief Functie voor het verzenden van informatie naar de server.
     * 
     * @param client WiFiClient object voor het maken van de verbinding.
     */
    void stuurInformatie(WiFiClient& client);
    int getId();  
    boolean status; // Variabele voor de huidige status van de sensor (true = geen beweging, false = beweging gedetecteerd)
private:
    const char* serverAddress;  // Het IP-adres of de hostname van de server
    int serverPort; // Het poortnummer van de server
    
    int id;
    int pirSensorPin;
    int ledIndicatorPin;
    
    unsigned long laagTijd; // Tijd wanneer de sensoruitgang laag gaat
    boolean timer;  // Variabele om de tijd sinds de laatste bewegingsdetectie bij te houden
    
    const int kalibratieTijd = 10; // Kalibratietijd voor de sensor
    const unsigned long pauze = 5000; // Tijd om aan te nemen dat beweging gestopt is
};

#endif  // MOTIONSENSOR_H