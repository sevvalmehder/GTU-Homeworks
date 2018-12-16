#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include "ISimulator.h"
#include <iostream>

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

	// Last updated time
	std::chrono::high_resolution_clock::time_point pressureLastUpd;

	// Period in millisecond
	int pressurePeriod;
	
	// Destructor
	~PressureControl();

private:

	ISimulator *simulator;
	std::thread *pressureThread;
	double currentPressure;

	// Configurable values
	const double A = 1.2;
	const double B = 0.8;

	// Thread beginning function
	void pressureTask();

	// Thread priority setting function
	void setPriority(int policy, int priority);

	

};

