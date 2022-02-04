#ifndef CHATTER_LIBRARY_CHATTER_H
#define CHATTER_LIBRARY_CHATTER_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Display/Display.h>
#include <Loop/LoopManager.h>
#include <Loop/LoopListener.h>
#include <Input/InputShift.h>
#include <Audio/Piezo.h>
#include <SPI.h>
#include "Pins.hpp"
#include "Battery/BatteryService.h"

class ChatterImpl {
public:
	ChatterImpl();
	void begin(bool backlight = true);

	/**
	 * Set backlight ON/OFF
	 * @param state true for on, false for off
	 */
	void setBacklight(bool state);

	Display* getDisplay();
	Input* getInput();
	SPIClass& getSPILoRa();

private:
	Display* display;
	InputShift* input;

	SPIClass spiLoRa;
};

extern ChatterImpl Chatter;
#endif
