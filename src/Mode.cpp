#include "Mode.hpp"
#include "Palettes.hpp"

Mode::Mode(){
	//даем контроллеру время передохнуть и подключиться к wifi
	delay(2000);
	//настраиваем ленту
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	//выставляем первоначальную яркость
    FastLED.setBrightness(BRIGHTNESS);
    //выставляем первоначальный режим подсветки
    currentPalette = bhw3_62_gp;
	//размытие (хз в чем разница, но вкл)
    currentBlending = LINEARBLEND;
}

Mode::~Mode(){}

void Mode::slightChange(int * def_value, int * cur_value, int val_chage = 1){
	//если модуль разницы значение больше чем значение val_chage (иначе будет жопа)
	if(abs((*cur_value) - (*def_value)) > val_chage){
		//если нынешнее значение больше эталоного
		if((*cur_value) > (*def_value)){
			//то уменьшаем нынешнее
			(*cur_value) -= val_chage;
		//если нынешнее значение меньше эталоного	
		}else {
			//увеличиваем его
			(*cur_value) += val_chage;
		}
	}
}

void Mode::FillLEDsFromPaletteColors( uint8_t colorIndex, uint8_t brightness){   
    for( int i = START_LED_INDEX; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void Mode::update(){
	static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */

	//если новый режим не соотвествует текущему
    if(MODE != NEWMODE){
		//уменьшаем яркость до нуля
		if(CURBRIGHTNESS > BRIGHT_CHANGE){
			CURBRIGHTNESS -= BRIGHT_CHANGE;
		//если яркость уже ноль - устанавливаем новый режим
		}else{
			Serial.println("update mode");
			MODE = NEWMODE;
			changeMode();
		}
	}
	//возращаем яркость если была смена режима
	//или при команде изменения яркости - плавное изменение 
	else{
		slightChange(&BRIGHTNESS, &CURBRIGHTNESS, BRIGHT_CHANGE);
	}

	//заполняем палетку
	FillLEDsFromPaletteColors(startIndex, CURBRIGHTNESS);
	//подаем подсветке
    FastLED.show();
	//ставим задержку
	//if(BRIGHTNESS==CURBRIGHTNESS && MODE == NEWMODE)
    	FastLED.delay(UPDATES_PER_SECOND);
	//else
	//FastLED.delay(UPDATES_PER_SECOND);
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
		NUM_LEDS = value;
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
		case 2: currentPalette = bhw1_05_gp;
				break;
		case 3: currentPalette = gr63_hult_gp;
				break;
		case 4: currentPalette = personPalette;
				break;
	};
}

void Mode::setBlending(int value){
	if (value == 0 || value == 1){
		currentBlending = (TBlendType)value;
	}
}

void Mode::setPersonPalette(byte array[]){
	personPalette=CRGBPalette16(array);
}
