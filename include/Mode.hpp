#ifndef MODE_HPP_
#define MODE_HPP_
#ifdef ESP32
    #define LED_PIN     32
#endif
#ifdef ESP8266
    #define LED_PIN  13
#endif
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

#include "Arduino.h"
#include <FastLED.h>


class Mode{
private:
    
    int MODE = 1; 
    int NEWMODE = 1;
    
    int BRIGHTNESS = 60;
    int CURBRIGHTNESS = 0; //если 0 - то плавный запуск

    int START_LED_INDEX = 0;
    int NUM_LEDS = 300; //при изменение - исправить значения в условиях в функциях setStartLed и setNumbLeds на NUM_LEDS+1

    int UPDATES_PER_SECOND = 10; //задержка обновления

    CRGB * leds = new CRGB[NUM_LEDS];

    CRGBPalette16 currentPalette;
    CRGBPalette16 personPalette; //палетка персональная
    TBlendType    currentBlending;

    void FillLEDsFromPaletteColors( uint8_t colorIndex, uint8_t brightness);

    void changeMode();
    void SetupTotallyRandomPalette();
    void slightChange(int * def_value, int * cur_value);
public:
    Mode();
    ~Mode();
   
    void update(void);
    void setBright(int value);
    void setStartLed(int value);
    void setNumbLeds(int value);
    void setDelay(int value);
    void setMode(int value);
    void setBlending(int value);
    void setPersonPalette(byte array[]);

     
};

#endif /* MODE_HPP_ */