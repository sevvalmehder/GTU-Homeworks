#include "TestSimulator.h"
#include <thread>
#include <iostream>

// ADC can read the value in 50 millisecond
#define ADC_PERIOD 10 

TestSimulator::TestSimulator(double initialPressure, double initialTemperature)
	:testPressure(initialPressure), testTemperature(initialTemperature)
{
	this->isTriggeredPressure = false;
	this->isTriggeredTemperature = false;
}

void TestSimulator::triggerADCPressure() {

	isTriggeredPressure = true;
	std::cout << "ADC Triggered for pressure" << std::endl;

}

void TestSimulator::triggerADCTemperature() {

	isTriggeredTemperature = true;
	std::cout << "ADC Triggered for temperature" << std::endl;

}

double TestSimulator::readADCPressure() {

	if (isTriggeredPressure) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ADC_PERIOD));
		return testPressure;
	}
	else {
		std::cerr << "ReadADCPressure failure...Did you trigger the ADC?" << std::endl;
		return -1;
	}

}

double TestSimulator::readADCTemperature() {
	
	if (isTriggeredTemperature) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ADC_PERIOD));
		return testTemperature;
	}
	else {
		std::cerr << "ReadADCTemperature failure...Did you trigger the ADC?" << std::endl;
		return -1;
	}


}

void TestSimulator::writeDACPump(const double value) {

	this->testPressure = value;
	
}

void TestSimulator::switchHeater(bool isOn) {

	if (isOn)
		this->testTemperature += 0.5;
	else
		this->testTemperature -= 0.2;

}


