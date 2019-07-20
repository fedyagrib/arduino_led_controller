#include "Mode.hpp"

Mode::Mode(){}

Mode::~Mode(){
	delete rgb_s;
}

void Mode::changeMode(void){
	Serial.printf("changeMode %d (empty)\n", mode);
	switch (mode)
	{
	case 0:
		Serial.printf("changeMode %d", mode);
		break;
	}
}

void Mode::changeBright(void){
	Serial.printf("changeBright %d (empty)\n", bright);
}

void Mode::changeRgb(void){
	Serial.printf("changeRgb %02x%02x%02x (empty)\n", rgb_s->red, rgb_s->green, rgb_s->blue);
}

void Mode::setMode (char value){
	mode = value;
	changeMode();
}

void Mode::setBright (char value){
	bright = value;
	changeBright();
}

void Mode::setRgb(Rgb_s * value){
	rgb_s = value;
	changeRgb();
}

