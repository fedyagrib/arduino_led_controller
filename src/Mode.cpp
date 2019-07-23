#include "Mode.hpp"
#include "Palettes.hpp"


Mode::Mode(){
	delay(2000);
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    
    currentPalette = bhw3_62_gp;
    currentBlending = LINEARBLEND;
}

Mode::~Mode(){}

void Mode::FillLEDsFromPaletteColors( uint8_t colorIndex, uint8_t brightness)
{   
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}



void Mode::update(){
	static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

	//плавное изменение яркости
	if(MODE == NEWMODE){
		if(BRIGHTNESS > CURBRIGHTNESS){
			CURBRIGHTNESS+=1;
		}
		if(BRIGHTNESS < CURBRIGHTNESS){
			CURBRIGHTNESS-=1;
		}
	}
	/* плавное уменьшение яркости до 0
	 * затем измнение режима 
	 * затем возращение прежней яркости
	 */

    else{
		if(CURBRIGHTNESS!=0){
			CURBRIGHTNESS-=1;
		}else{
			MODE = NEWMODE;
			changeMode();
		}
	}

	FillLEDsFromPaletteColors(startIndex, CURBRIGHTNESS);
    FastLED.show();
    FastLED.delay(UPDATES_PER_SECOND);
}

void Mode::setBright(int value){
	if(value>0){
		BRIGHTNESS = value % 256;
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
		NEWMODE = value;
		
	}
}

void Mode::changeMode(){
	switch (MODE){
		case 0: currentPalette = SetupTotallyRandomPalette();
				break;
		case 1: currentPalette = bhw3_62_gp;
				break;
		case 2: currentPalette = bhw3_61_gp;
				break;
		case 3: currentPalette = gr63_hult_gp;
				break;		
	};
}

void Mode::setBlending(int value){
	if (value == 0 || value == 1){
		currentBlending = (TBlendType)value;
	}
}
