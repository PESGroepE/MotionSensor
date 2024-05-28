#include "RGBLeds.h"

/**
 * @brief Constructor voor de RGBLeds klasse
 *
 * Initialiseert de LED's met het opgegeven aantal, pin en kleurenindeling.
 */
RGBLeds::RGBLeds() : leds(AANTAL_LEDS, PIN, NEO_GRB + NEO_KHZ800) {
    leds.begin();
    leds.setBrightness(100);
    leds.clear();
    leds.show();
}

/**
 * @brief Zet het brandlicht aan
 *
 * Het brandlicht zal in groepen van de opgegeven grootte rood oplichten.
 */
void RGBLeds::brandlichtAan() {
    for(int i = 0; i <= AANTAL_LEDS - GROEP; i++) {
        for(int j = 0; j < GROEP; j++) {
            leds.setPixelColor(i + j, leds.Color(255, 0, 0));
        }
        leds.show();
        delay(20);
        leds.clear();
    }
}

/**
 * @brief Zet het entreelicht aan
 *
 * Het entreelicht zal alle LED's wit laten oplichten.
 */
void RGBLeds::entreelichtAan(){
    for(int i = 0; i < AANTAL_LEDS; i++){
        leds.setPixelColor(i, leds.Color(255, 255, 255));
    }
    leds.show();
    delay(100);
}

/**
 * @brief Schakel de verlichting uit
 *
 * Alle LED's worden uitgeschakeld.
 */
void RGBLeds::lichtUit(){
    for(int i = 0; i < AANTAL_LEDS; i ++){
        leds.setPixelColor(i, leds.Color(0, 0, 0));
    }
    leds.show();
    delay(100);
}
