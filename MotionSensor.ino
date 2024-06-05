#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "RGBLeds.h"

const char* ssid = "pigroep5";
const char* password = "pigroep5";
const char* serverAddress = "10.0.10.1";
const int serverPort = 8080;
const String host = "10.0.10.1:8080";

WiFiClient client;
HTTPClient http;
RGBLeds strip;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void loop() {
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
  if (http.begin(client, url)) {                  // HTTP
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
        strip.setKleur(255, 255, 255);
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