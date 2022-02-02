#ifndef CHATTER_LIBRARY_SETTINGS_H
#define CHATTER_LIBRARY_SETTINGS_H

#include <Arduino.h>

const uint8_t ShutdownMinutes[] = {0, 5, 10, 15, 20};

struct SettingsData {
	bool sound = false;
	uint8_t sleepTime = 1; //index of value in vector, values : {0, 1, 5, 15, 30}[min]
	uint32_t screenBrightness = 255; // speed * (speedMultiplier / 255)

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
