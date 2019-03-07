/*
 * A simulator implementing the following interface
 * will be used during evaluation tests.
 */

#pragma once

class ISimulator {

public:
	virtual void triggerADCPressure() = 0;
	virtual void triggerADCTemperature() = 0;
	virtual double readADCPressure() = 0;
	virtual double readADCTemperature() = 0;
	virtual void writeDACPump(const double value) = 0;
	virtual void switchHeater(bool isOn) = 0;

};