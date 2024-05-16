#include "MotionSensor.h" // Inclusie van de headerbestanden voor de MotionSensor klasse
#include <ESP8266HTTPClient.h>  // Inclusie van de headerbestanden voor de ESP8266 HTTP-client
#include <Adafruit_NeoPixel.h>  // Inclusie van de headerbestanden voor de Adafruit NeoPixel bibliotheek

////////////////////////////////////////////
const int numleds = 60; // Aantal LED's in de LED-strip
const int ledstrippin = D6; // Pinnummer waaraan de LED-strip is aangesloten
Adafruit_NeoPixel leds = Adafruit_NeoPixel(numleds, ledstrippin); // Instantiëring van het NeoPixel object
////////////////////////////////////////////

// WIFI-instellingen
const char* ssid = "pigroep5"; // Vervang door je WiFi SSID
const char* password = "pigroep5"; // Vervang door je WiFi wachtwoord

// Serverinstellingen
const char* serverAddress = "10.0.10.1"; // Vervang door het IP-adres of de hostname van je server
const int serverPort = 8080; // Poortnummer van de server

MotionSensor motionSensor1(serverAddress, serverPort, 5, BUILTIN_LED, 1); // Instantiëring van het MotionSensor object
MotionSensor motionSensor2(serverAddress, serverPort, 4, BUILTIN_LED, 2); // Instantiëring van het MotionSensor object
WiFiClient client;  // Instantiëring van het WiFiClient object
HTTPClient http;  // Instantiëring van het HTTPClient object
/**
 * @brief Functie voor de initiële setup van de Arduino.
 */
void setup() {
    Serial.begin(115200); // Start de seriële communicatie
    leds.begin(); // Initialiseer de NeoPixel LED-strip

    WiFi.begin(ssid, password); // Verbind met het WiFi-netwerk

    // Wacht tot de verbinding tot stand is gebracht
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");  // Geef aan dat de verbinding tot stand is gebracht
    Serial.println(WiFi.localIP()); // Geef aan dat de verbinding tot stand is gebracht

    motionSensor1.initialisatie(); // Geef aan dat de verbinding tot stand is gebracht
    motionSensor2.initialisatie(); // Geef aan dat de verbinding tot stand is gebracht
}
/**
 * @brief Functie die continu wordt uitgevoerd na de setup.
 */
void loop() {
    motionSensor1.startDetectie(); // Start de bewegingsdetectie
    motionSensor2.startDetectie(); // Start de bewegingsdetectie
    motionSensor1.stuurInformatie(client); // Stuur informatie naar de server
    motionSensor2.stuurInformatie(client); // Stuur informatie naar de server
    delay(100); // Wacht kort

  // GET-verzoek
  String host = "10.0.10.1:8080";  // Vervang door het IP-adres of hostname van je Raspberry Pi
  String url = "http://" + host + "/led/status";  // Zorg dat dit het juiste endpoint is

  // Voer het GET-verzoek uit
  if (http.begin(client, url)) {  // HTTP
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    // Controleer de HTTP-statuscode
    if (httpCode < 0) {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    } else if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      String payload = http.getString();  // Ontvang het antwoord van de server
      Serial.println(payload);  // Geef het ontvangen bericht weer
      if (payload=="1") {    
          // Aan
          for (int i=0; i<numleds; i++) {
             leds.setPixelColor(i, leds.Color(255, 255, 255));
          }
          leds.show();  // Toon de LED-status
      } else {
         // Uit
          for (int i=0; i<numleds; i++) {
             leds.setPixelColor(i, leds.Color(0, 0, 0));
          }
          leds.show();  // Toon de LED-status
      }
      // Verwerk het ontvangen bericht om te bepalen of het licht aan of uit moet
      // Bijvoorbeeld: if (payload == "ON") { ... }
    }
    http.end(); // Sluit de HTTP-client af
  } else {
    Serial.println("[HTTP] Unable to connect"); // Geef aan dat er geen verbinding mogelijk is
  }
}