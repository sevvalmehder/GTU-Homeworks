#pragma once

#include <thread>
#include "ISimulator.h"

class PressureControl
{
public:
	// Constructor
	PressureControl(ISimulator* sim, int frequency, double initialPressure);

	// Getter for current pressure
	double getCurrentPressure();

	// Destructor
	~PressureControl();

private:

	ISimulator *simulator;
	std::thread *pressureThread;
	double currentPressure;

	// Period in millisecond
	int pressurePeriod;

	// Configurable values
	const double A = 1.2;
	const double B = 0.8;

	// Thread beginning function
	void pressureTask();

	

};

