#include "MotionSensor.h"
#include <ESP8266HTTPClient.h>
// #include <Adafruit_NeoPixel.h>
#include "RGBLeds.h"


// Define the number of LEDs in the strip
// #define NUM_LEDS 60
// #define LED_PIN D6

// Create an instance of the Adafruit_NeoPixel class
// Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
RGBLeds strip;

// WiFi settings
const char* ssid = "pigroep5"; // Vervang door je WiFi SSID
const char* password = "pigroep5"; // Vervang door je WiFi wachtwoord

// Server settings
const char* serverAddress = "10.0.10.1"; // Vervang door het IP-adres of de hostname van je server
const int serverPort = 8080; // Poortnummer van de server

String host = "10.0.10.1:8080";  // Vervang door het IP-adres of hostname van je Raspberry Pi

bool previousStatus = false;

MotionSensor motionSensor(serverAddress, serverPort);
WiFiClient client;
HTTPClient http;

void setup() {
    Serial.begin(115200);

    // Initialize the NeoPixel strip
    // strip.begin();
    // strip.setBrightness(25);
    // strip.show(); // Initialize all pixels to 'off'

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());

    motionSensor.initialisatie();
}

void loop() {
    //motionSensor.startDetectie(client);
    //delay(100);
    if (getBrand()) return;
    getColor();
    getStatus();
    delay(1000);
  
}

/**
  * @brief Haal de status van de leds op
  */
void getStatus() {
  // Get request
    String url = "http://" + host + "/led/status";  // Zorg dat dit het juiste endpoint is

    if (http.begin(client, url)) {  // HTTP
        Serial.print("[HTTP] GET...\n");
        int httpCode = http.GET();

        // httpCode zal negatief zijn bij een fout
        if (httpCode < 0) {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        } else if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();
            Serial.println(payload);
            if (payload == "1") {    
                // aan
                strip.entreelichtAan();
            } else {
                // uit
                strip.lichtUit();
            }
        }
        http.end();
    } else {
        Serial.println("[HTTP] Unable to connect");
    }

    delay(100);
}

/**
  * @brief Haal de kleur van de leds op
  */
void getColor() {
  // Get request
    String url = "http://" + host + "/led/color";  // Zorg dat dit het juiste endpoint is

    if (http.begin(client, url)) {  // HTTP
        Serial.print("[HTTP] GET...\n");
        int httpCode = http.GET();

        // httpCode zal negatief zijn bij een fout
        if (httpCode < 0) {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        } else if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();
            Serial.println(payload);
            if (payload == "rood") {    
                strip.setKleur(255, 0, 0);
            } else if (payload == "groen") {  
                strip.setKleur(0, 255, 0);
            } else if (payload == "blauw") {  
                strip.setKleur(0, 0, 255);
            } else if (payload == "wit") {
                strip.setKleur(255,255,255);
            }
        }
        http.end();
    } else {
        Serial.println("[HTTP] Unable to connect");
    }

    delay(100);
}

/**
  * @brief Haal de status van het brandalarm op
  */
bool getBrand() {
  // Get request
    String url = "http://" + host + "/led/brand";  // Zorg dat dit het juiste endpoint is

    if (http.begin(client, url)) {  // HTTP
        Serial.print("[HTTP] GET...\n");
        int httpCode = http.GET();

        // httpCode zal negatief zijn bij een fout
        if (httpCode < 0) {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        } else if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();
            Serial.println(payload);
            if (payload == "1") {    
                strip.brandlichtAan();
                return true;
            } else {
                return false;
            }
        }
        http.end();
    } else {
        Serial.println("[HTTP] Unable to connect");
    }

    delay(100);
    return false;
}