#pragma once

#include <thread>
#include "PressureControl.h"
#include "TemperatureControl.h"
class OperatorConsole
{
public:
	OperatorConsole(int frequency, PressureControl& pressureRef, TemperatureControl& temperatureRef);
	~OperatorConsole();
private:
	std::thread *consoleThread;
	int consolePeriod;

	// Reference of other related task's object
	PressureControl& pControl;
	TemperatureControl& tControl;

	void consoleTask();
};

