#include "Chatter.h"
#include <Loop/LoopManager.h>
#include "Pins.hpp"
#include <LoRa.h>
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

	pinMode(SHIFT_DATA, OUTPUT);
	pinMode(SHIFT_CLOCK, OUTPUT);
	pinMode(SHIFT_PIN, INPUT);

	inputShift = new InputShift(2,SHIFT_DATA,SHIFT_CLOCK,SHIFT_PIN);
	inputShift->preregisterButtons({BTN_0, BTN_8, BTN_5, BTN_2, BTN_1, BTN_4, BTN_7, BTN_L, BTN_BACK, BTN_ENTER, BTN_DOWN, BTN_UP, BTN_3, BTN_6, BTN_9, BTN_R});
	LoopManager::addListener(Input::getInstance());
	
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
