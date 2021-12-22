#include "Chatter.h"
#include <Loop/LoopManager.h>
#include "Pins.hpp"
#include <SPIFFS.h>

ChatterImpl Chatter;

void ChatterImpl::begin(){
	Serial.begin(115200);

	display = new Display(160, 128, BL_PIN, 3);
	display->begin();
	display->swapBytes(false);
	display->setPower(false);
	display->getBaseSprite()->clear(TFT_BLACK);
	display->commit();

	if(!SPIFFS.begin()){
		Serial.println("SPIFFS failed");
	}


	inputShift = new InputShift(23, 22, 21, 16);
	inputShift->begin();
	LoopManager::addListener(inputShift);

	/*SPI.begin(16,17,5,-1);
	LoRa.setSPI(SPI);
	LoRa.setPins(ss,rst,dio0);
	LoRa.setTxPower(20);
	LoRa.setSpreadingFactor(12);
	LoRa.setSignalBandwidth(250E3);
	LoRa.setCodingRate4(5);

	while (!LoRa.begin(868E6)) {
		Serial.println(".");
		delay(500);
	}*/
}

void ChatterImpl::loop(uint micros){

}

Display* ChatterImpl::getDisplay(){
	return display;
}

Input* ChatterImpl::getInput(){
	return inputShift;
}
