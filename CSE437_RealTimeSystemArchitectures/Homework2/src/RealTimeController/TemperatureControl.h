#pragma once

#include "ISimulator.h"
#include <thread>

class TemperatureControl
{
public:
	// Constructor
	TemperatureControl(ISimulator* sim, int frequency, double initialTemperature);

	// Getter for current temperature
	double getCurrentTemperature();

	// Destructor
	~TemperatureControl();

private:
	ISimulator *simulator;
	std::thread *temperatureThread;
	double currentTemperature;

	// Period in millisecond
	int temperaturePeriod;

	// Configurable values
	const double C = 25;
	const double D = 35;

	// Thread beginning function
	void temperatureTask();

};

