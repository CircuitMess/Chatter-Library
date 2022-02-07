#include "Chatter.h"
#include <Loop/LoopManager.h>
#include "Pins.hpp"
#include "Battery/BatteryService.h"
#include "Settings.h"
#include <SPIFFS.h>

ChatterImpl Chatter;

ChatterImpl::ChatterImpl() : spiLoRa(HSPI){}

void ChatterImpl::begin(bool backlight){
	Serial.begin(115200);

	pinMode(PIN_BL, OUTPUT);
	digitalWrite(PIN_BL, 1);
	Piezo.begin(PIN_BUZZ);

	display = new Display(160, 128, -1, 3);
	display->begin();
	display->getTft()->setRotation(1);
	display->swapBytes(false);
	display->getBaseSprite()->clear(TFT_BLACK);
	display->commit();

	if(!SPIFFS.begin()){
		Serial.println("SPIFFS failed");
	}

	Settings.begin();

	input = new InputShift(INPUT_DATA, INPUT_CLOCK, INPUT_LOAD, 16);
	input->begin();

	Vector<uint8_t> buttons;
	for(int i = 0; i < 16; i++){
		buttons.push_back(i);
	}
	input->preregisterButtons(buttons);

	LoopManager::addListener(input);

	spiLoRa.begin(RADIO_SCK, RADIO_MISO, RADIO_MOSI, RADIO_CS);

	Battery.begin();

	ledcSetup(1, 5000, 8);
	ledcAttachPin(PIN_BL, 1);
	if(backlight){
		fadeIn();
	}
}

void ChatterImpl::setBrightness(uint8_t brightness){
	ledcWrite(1, map(brightness, 0, 255, 180, 0));
}

Display* ChatterImpl::getDisplay(){
	return display;
}

Input* ChatterImpl::getInput(){
	return input;
}

SPIClass &ChatterImpl::getSPILoRa(){
	return spiLoRa;
}

void ChatterImpl::fadeOut(){
	for(int i = 0; i <= 255; ++i){
		ledcWrite(1, map(Settings.get().screenBrightness, 0, 255, 180, 0) * (1 - i / 255.0) + i);
		delay(1);
	}
}

void ChatterImpl::fadeIn(){
	for(int i = 0; i <= 255; ++i){
		ledcWrite(1, int(255.0 - i * (1 - map(Settings.get().screenBrightness, 0, 255, 180, 0) / 255.0)));
		delay(1);
	}
}
