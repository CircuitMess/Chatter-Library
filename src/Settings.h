#ifndef CHATTER_LIBRARY_SETTINGS_H
#define CHATTER_LIBRARY_SETTINGS_H

#include <Arduino.h>

const uint8_t ShutdownMinutes[] = {0, 5, 10, 15, 20};

struct SettingsData {
	bool sound = true;
	uint8_t sleepTime = 1; //index of value in vector, values : {0, 5, 10, 15, 20}[min]
	uint32_t screenBrightness = 255;

};

class SettingsImpl {
public:
	bool begin();

	void store();

	SettingsData& get();

	void reset();

private:
	SettingsData data;
};

extern SettingsImpl Settings;

#endif //CHATTER_LIBRARY_SETTINGS_H
