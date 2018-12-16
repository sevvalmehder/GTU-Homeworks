#pragma once

#include "ISimulator.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

class TemperatureControl
{
public:
	// Constructor
	TemperatureControl(ISimulator* sim, int frequency, double initialTemperature);

	// Getter for current temperature
	double getCurrentTemperature();

	// This thread write to currentTemperature variable
	// and console thread read this value. We need to
	// mutex&condition variable beware of race condition.
	// isReaded is for control
	std::mutex mutexTemperature;
	std::condition_variable cv;

	// Last updated time
	std::chrono::high_resolution_clock::time_point tempLastUpd;

	// Period in millisecond
	int temperaturePeriod;
	
	// Destructor
	~TemperatureControl();

private:
	ISimulator *simulator;
	std::thread *temperatureThread;
	double currentTemperature;

	

	// Configurable values
	const double C = 25;
	const double D = 35;

	// Thread beginning function
	void temperatureTask();

	// Thread priority setting function
	void setPriority(int policy, int priority);

};

