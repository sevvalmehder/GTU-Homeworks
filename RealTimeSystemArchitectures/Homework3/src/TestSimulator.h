/*
 * @author: Sevval MEHDER
 * Implementation of ISimulator interface for testing the system.
 */
#pragma once

#include "ISimulator.h"

class TestSimulator : public ISimulator {

public:	

	// Constructor
	TestSimulator(double initialPressure, double initialTemperature);

	// ISimulator functions
	void triggerADCPressure();
	void triggerADCTemperature();
	double readADCPressure();
	double readADCTemperature();
	void writeDACPump(const double value);
	void switchHeater(bool isOn);

	// ISimulator class variables
	double testPressure;
	double testTemperature;

	// Control variables for trigger operations
	bool isTriggeredPressure;
	bool isTriggeredTemperature;

};

