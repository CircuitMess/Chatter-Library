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
	 * Set backlight brightness
	 * @param brightness brightness value from 0 to 255, internally scaled to 51 - 255
	 */
	void setBrightness(uint8_t brightness);

	Display* getDisplay();
	Input* getInput();
	SPIClass& getSPILoRa();

	void fadeIn();
	void fadeOut();

private:
	Display* display;
	InputShift* input;

	SPIClass spiLoRa;
};

extern ChatterImpl Chatter;
#endif
