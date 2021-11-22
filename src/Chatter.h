#ifndef CHATTER_LIBRARY_CHATTER_H
#define CHATTER_LIBRARY_CHATTER_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Display/Display.h>
#include <Loop/LoopListener.h>

class ChatterImpl : public LoopListener{
public:
	void begin();
	void loop(uint micros) override;

	Display* getDisplay();

private:
	Display* display;
};

extern ChatterImpl Chatter;
#endif
