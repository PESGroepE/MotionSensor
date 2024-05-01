#include "MotionSensor.h"
#include <ESP8266HTTPClient.h>
#include <Adafruit_NeoPixel.h>

////////////////////////////////////////////
const int numleds = 10;
const int ledstrippin = D6;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(numleds, ledstrippin);

////////////////////////////////////////////

//wifi settings
const char* ssid = "pigroep5"; // Vervang door je WiFi SSID
const char* password = "pigroep5"; // Vervang door je WiFi wachtwoord

//server settings
const char* serverAddress = "10.0.10.2"; // Vervang door het IP-adres of de hostname van je server
const int serverPort = 8080; // Poortnummer van de server

MotionSensor motionSensor(serverAddress, serverPort);
WiFiClient client;
HTTPClient http;

void setup() {
    Serial.begin(115200);

///////////////////////////////////////////
    leds.begin();
///////////////////////////////////////////


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
    motionSensor.startDetectie();
    motionSensor.stuurInformatie(client);
    delay(100);


    /////////////////////////////////////////////////////
    //Get request
  String host = "10.0.10.2:8080";  // Vervang door het IP-adres of hostname van je Raspberry Pi
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
      if (payload=="1") {    
          //aan
          for (int i=0; i<numleds; i++) {
             leds.setPixelColor(0, leds.Color(255, 255, 255));
          }
          leds.show();
      } else {
        //uit
          for (int i=0; i<numleds; i++) {
             leds.setPixelColor(0, leds.Color(0, 0, 0));
          }
          leds.show();
      }
      // Hier kun je de payload verwerken om te bepalen of het licht aan of uit moet
      // Bijvoorbeeld: if (payload == "ON") { ... }
    }
    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }
}