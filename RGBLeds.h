#ifndef RGBLEDS_H
#define RGBLEDS_H

#include <Adafruit_NeoPixel.h>

/**
 * @brief Klasse voor het aansturen van RGB LED's
 */
class RGBLeds {
public:
    /**
     * @brief Constructor voor de RGBLeds klasse
     */
    RGBLeds();

    /**
     * @brief Zet het merklicht aan
     */
    void brandlichtAan();

    /**
     * @brief Zet het entreelicht aan
     */
    void entreelichtAan();

    /**
     * @brief Schakel de verlichting uit
     */
    void lichtUit();

    void setKleur(int, int, int);

private:
    static const int PIN = D6; ///< Pinnummer voor het aansturen van de LED's
    static const int AANTAL_LEDS = 60; ///< Totaal aantal LED's
    static const int GROEP = 10; ///< Aantal LED's per groep

    Adafruit_NeoPixel leds; ///< Object voor het aansturen van NeoPixel LED's
    int r, g, b;
};

#endif
