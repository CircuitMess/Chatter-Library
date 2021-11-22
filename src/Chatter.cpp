#include "Chatter.h"
#include <Loop/LoopManager.h>
#include "Pins.hpp"
#include <LoRa.h>

ChatterImpl Chatter;

void ChatterImpl::begin(){
	Serial.begin(115200);

	pinMode(BL_PIN,OUTPUT);
	digitalWrite(BL_PIN,LOW);
	display = new Display(128, 160, -1, 0);
	display->begin();
	display->getBaseSprite()->clear(TFT_BLACK);
	display->commit();

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
