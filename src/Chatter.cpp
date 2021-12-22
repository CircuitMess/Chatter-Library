#include "Chatter.h"
#include <Loop/LoopManager.h>
#include "Pins.hpp"
#include <SPIFFS.h>

ChatterImpl Chatter;

void ChatterImpl::begin(){
	Serial.begin(115200);

	pinMode(PIN_BL, OUTPUT);
	pinMode(PIN_BL, HIGH);

	Piezo.begin(PIN_BUZZ);

	display = new Display(160, 128, PIN_BL, 3);
	display->begin();
	display->swapBytes(false);
	display->setPower(false);
	display->getBaseSprite()->clear(TFT_BLACK);
	display->commit();

	if(!SPIFFS.begin()){
		Serial.println("SPIFFS failed");
	}

	input = new InputShift(INPUT_DATA, INPUT_CLOCK, INPUT_LOAD, 16);
	input->begin();
	LoopManager::addListener(input);

	digitalWrite(PIN_BL, LOW);
}

void ChatterImpl::loop(uint micros){

}

Display* ChatterImpl::getDisplay(){
	return display;
}

Input* ChatterImpl::getInput(){
	return input;
}
