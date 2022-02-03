#include "Chatter.h"
#include <Loop/LoopManager.h>
#include "Pins.hpp"
#include "Battery/BatteryService.h"
#include "Settings.h"
#include <SPIFFS.h>

ChatterImpl Chatter;

ChatterImpl::ChatterImpl() : spiLoRa(HSPI){}

void ChatterImpl::begin(){
	Serial.begin(115200);

	pinMode(PIN_BL, OUTPUT);
	pinMode(PIN_BL, HIGH);

	Piezo.begin(PIN_BUZZ);

	display = new Display(160, 128, PIN_BL, 3);
	display->begin();
	display->getTft()->setRotation(1);
	display->swapBytes(false);
	display->setPower(false);
	display->getBaseSprite()->clear(TFT_BLACK);
	display->commit();

	if(!SPIFFS.begin()){
		Serial.println("SPIFFS failed");
	}
	Settings.begin();
	input = new InputShift(INPUT_DATA, INPUT_CLOCK, INPUT_LOAD, 16);
	input->begin();
	LoopManager::addListener(input);

	spiLoRa.begin(RADIO_SCK, RADIO_MISO, RADIO_MOSI, RADIO_CS);

	Battery.begin();

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

SPIClass& ChatterImpl::getSPILoRa(){
	return spiLoRa;
}
