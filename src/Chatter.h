#ifndef CHATTER_LIBRARY_CHATTER_H
#define CHATTER_LIBRARY_CHATTER_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Display/Display.h>
#include <Loop/LoopListener.h>
#include <Input/InputShift.h>
#include "Pins.hpp"

class ChatterImpl : public LoopListener, public InputListener{
public:
	void begin();
	void loop(uint micros) override;

	Display* getDisplay();

private:
	Display* display;
	InputShift* inputShift;

};

extern ChatterImpl Chatter;
#endif
