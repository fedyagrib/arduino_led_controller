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

void Mode::slightChange(int * def_value, int * cur_value, bool clean_min, bool clean_max){
	if((*cur_value) != (*def_value)){
		if((*cur_value) > (*def_value)){
			Serial.println("if");
			(*cur_value)--;
			if (clean_max)
				FastLED.clear();
		}else if ((*cur_value) < (*def_value)){
			(*cur_value)++;
			if (clean_min)
				FastLED.clear();
		}
	}
}

void Mode::FillLEDsFromPaletteColors( uint8_t colorIndex, uint8_t brightness)
{   
	slightChange(&START_LED_INDEX, &CUR_START_LED_INDEX, true, false);
	slightChange(&NUM_LEDS, &CUR_NUM_LEDS, true, true);

    for( int i = CUR_START_LED_INDEX; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void Mode::update(){
	static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

	//плавное изменение яркости
	if(MODE == NEWMODE){
		slightChange(&BRIGHTNESS, &CURBRIGHTNESS);
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
	if(value >= 0 && value < 301){
		START_LED_INDEX = value;
	}

}
void Mode::setNumbLeds(int value){
	if(value >= 0 && value < 301){
		CUR_NUM_LEDS = value;
	}
}

void Mode::setDelay(int value){
	if(value >= 0){
		UPDATES_PER_SECOND = value;
	}

}

void Mode::setMode(int value){
	if (value >= 0){
		NEWMODE = value;
	}
}

void Mode::SetupTotallyRandomPalette(){
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

void Mode::changeMode(){
	switch (MODE){
		case 0: SetupTotallyRandomPalette();
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
