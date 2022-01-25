#include "BatteryService.h"
#include <Loop/LoopManager.h>

BatteryService Battery;

const uint16_t BatteryService::MeasureInterval = 10; //in seconds
const uint16_t BatteryService::MeasureCount = 10; //in seconds

void BatteryService::loop(uint micros){
	measureMicros += micros;
	if(measureMicros >= (MeasureInterval * 1000000) / MeasureCount){
		measureMicros = 0;
		measureSum += analogRead(BATTERY_PIN);
		measureCounter++;
		if(measureCounter == MeasureCount){
			measureSum = measureSum / MeasureCount;
			voltage = map(measureSum,0,960,3700,4300);
			measureCounter = 0;
			measureSum = 0;
		}
		measureMicros = 0;
	}
}

void BatteryService::begin(){
  LoopManager::addListener(this);
  pinMode(BATTERY_PIN,INPUT);

  double ukupno = 0;

  for(int i=0;i<10;i++){
	  ukupno = ukupno + analogRead(BATTERY_PIN);
  }

}

uint8_t BatteryService::getLevel() const{
	uint8_t percentage = getPercentage();
	if(percentage > 80){
		return 4;
	}else if(percentage <= 80 && percentage > 40){
		return 3;
	}else if(percentage <= 40 && percentage > 15){
		return 2;
	}else if(percentage <= 15 && percentage > 5){
		return 1;
	}else if(percentage <= 5){
		return 0;
	}
}

uint8_t BatteryService::getPercentage() const{
	int16_t percentage = map(getVoltage(), 0, 4500, 0, 100);
	if(percentage < 0){
		return 0;
	}else if(percentage > 100){
		return 100;
	}else{
		return percentage;
	}
}

uint16_t BatteryService::getVoltage() const{
	return voltage;
}
