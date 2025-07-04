#include "BatteryService.h"
#include <Loop/LoopManager.h>
#include <soc/efuse_reg.h>
#include <Util/HWRevision.h>
#include "../Pins.hpp"

BatteryService Battery;


uint16_t BatteryService::mapReading(uint16_t reading){
	if(HWRevision::get() == 1){
		// At 3600 reading 3600, at 4600 reading 4850
		/*const int volt1 = reading * 4;
		const int volt2 = std::round(((float) (volt1 - 3600) / 1250.0f) * 250.0f);
		return volt1 - volt2;*/

		const int volt1 = reading * 4;
		return map(volt1, 3780, 5030, 3600, 4600);
	}else{
		return map(reading, 720, 920, 3700, 4500);
	}
}

void BatteryService::loop(uint micros){
	measureMicros += micros;
	if(measureMicros >= (MeasureInterval * 1000000) / MeasureCount){
		measureMicros = 0;
		measureSum += analogRead(BATTERY_PIN);
		measureCounter++;
		if(measureCounter == MeasureCount){
			measureSum = measureSum / MeasureCount;
			voltage = measureSum;
			measureCounter = 0;
			measureSum = 0;
		}
	}
}

void BatteryService::begin(){
	LoopManager::addListener(this);
	pinMode(BATTERY_PIN, INPUT);

	if(HWRevision::get() == 1){
		// TODO: Check if this stays low during deep sleep
		pinMode(CALIB_EN, OUTPUT);
		digitalWrite(CALIB_EN, 0);

		calibrate();
	}

	for(int i = 0; i < 10; i++){
		measureSum += analogRead(BATTERY_PIN);
	}
	measureSum = measureSum / MeasureCount;
	voltage = measureSum;
	measureSum = 0;
}

uint8_t BatteryService::getLevel() const{
	uint8_t percentage = getPercentage();
	if(percentage > 80){
		return 5;
	}else if(percentage > 60){
		return 4;
	}else if(percentage > 40){
		return 3;
	}else if(percentage > 20){
		return 2;
	}else if(percentage >= 5){
		return 1;
	}else if(percentage < 5){
		return 0;
	}
}

uint8_t BatteryService::getPercentage() const{
	int16_t percentage = map(getVoltage(), 3700, 4500, 0, 100);
	if(percentage < 0){
		return 0;
	}else if(percentage > 100){
		return 100;
	}else{
		return percentage;
	}
}

uint16_t BatteryService::getVoltage() const{
	if(HWRevision::get() == 1){
		return mapReading(voltage + getVoltOffset());
	}else{
		return mapReading(voltage) + getVoltOffset();
	}
}

int16_t BatteryService::getVoltOffset() const{
	if(HWRevision::get() == 1){
		return calibOffset;
	}else{
		uint32_t upper = REG_GET_FIELD(EFUSE_BLK3_RDATA3_REG, EFUSE_RD_ADC1_TP_HIGH);
		uint32_t lower = REG_GET_FIELD(EFUSE_BLK3_RDATA3_REG, EFUSE_RD_ADC1_TP_LOW);
		return (upper << 7) | lower;
	}
}

void BatteryService::calibrate(){
	digitalWrite(CALIB_EN, 1);
	delay(100);

	float sum = 0;
	for(int i = 0; i < MeasureCount; i++){
		sum += analogRead(CALIB_READ);
	}
	const uint16_t volt = std::round(sum / (float) MeasureCount);

	calibOffset = CalibRef - volt;

	digitalWrite(CALIB_EN, 0);
	delay(100);
}
