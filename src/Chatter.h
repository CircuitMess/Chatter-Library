#ifndef CHATTER_LIBRARY_CHATTER_H
#define CHATTER_LIBRARY_CHATTER_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Display/Display.h>
#include <Loop/LoopManager.h>
#include <Loop/LoopListener.h>
#include <Input/InputShift.h>
#include <Audio/Piezo.h>
#include "Pins.hpp"

class ChatterImpl : public LoopListener, public InputListener{
public:
	void begin();
	void loop(uint micros) override;

	Display* getDisplay();
	Input* getInput();

private:
	Display* display;
	InputShift* input;

};

extern ChatterImpl Chatter;
#endif
