#include "Mode.hpp"
#include "Palettes.hpp"


Mode::Mode(){
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    
    setMode(MODE);
    currentBlending = LINEARBLEND;
}

Mode::~Mode(){}

void Mode::FillLEDsFromPaletteColors( uint8_t colorIndex)
{ 
    for( int i = START_LED_INDEX; i < NUM_LEDS + START_LED_INDEX; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
        colorIndex += 3;
    }
}

void Mode::update(){
	static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(UPDATES_PER_SECOND);
}

void Mode::setBright(int value){
	if(value>0){
		BRIGHTNESS = value % 256;
		FastLED.setBrightness(BRIGHTNESS);
	}

}
void Mode::setStartLed(int value){
	if(value > 0 && value < 301){
		START_LED_INDEX = value;
		if (value + NUM_LEDS > 300){
			NUM_LEDS = 300 - START_LED_INDEX;
		}
		FastLED.clear();
	}

}
void Mode::setNumbLeds(int value){
	if(value > 0 && value < 301){
		NUM_LEDS = value;
		if (value + NUM_LEDS > 300){
			START_LED_INDEX = 300 - NUM_LEDS;
		}
		FastLED.clear();
	}
}

void Mode::setDelay(int value){
	if(value>0){
		UPDATES_PER_SECOND = value;
	}

}

void Mode::setMode(int value){
	if (value > 0){
		if (value != MODE){
			switch (value){
				case 0: currentPalette = bhw3_62_gp;
						break;
				case 1: currentPalette = bhw3_61_gp;
						break;
				case 2: currentPalette = gr63_hult_gp;
						break;		
			};
		}
	}
}

void Mode::setBlending(int value){
	if (value == 0 || value == 1){
		currentBlending = (TBlendType)value;
	}
}
