#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include "ISimulator.h"

class PressureControl
{
public:
	// Constructor
	PressureControl(ISimulator* sim, int frequency, double initialPressure);

	// Getter for current pressure
	double getCurrentPressure();

	// This thread write to currentPressure variable
	// and console thread read this value. We need to
	// mutex&condition variable beware of race condition.
	// isReaded is for control
	std::mutex mutexPressure;
	std::condition_variable cv;
	bool isReaded;

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

