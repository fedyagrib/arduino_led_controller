#ifndef MODE_HPP_
#define MODE_HPP_

#define LED_PIN     32
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

#include "Arduino.h"
#include <FastLED.h>


class Mode{
private:
    
    int MODE = 0; 
    int START_LED_INDEX = 0;
    int NUM_LEDS  =  300;
    int BRIGHTNESS = 150;
    int UPDATES_PER_SECOND = 10;

    CRGB * leds = new CRGB[NUM_LEDS];

    CRGBPalette16 currentPalette ;
    TBlendType    currentBlending;

    void FillLEDsFromPaletteColors( uint8_t colorIndex);

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
     
};

#endif /* MODE_HPP_ */