#include "TemperatureControl.h"

#define MILLISECOND 1000

using HRC = std::chrono::high_resolution_clock;

TemperatureControl::TemperatureControl(ISimulator* sim, int frequency, double initialTemperature)
	:simulator(sim), temperaturePeriod( MILLISECOND / frequency), currentTemperature(initialTemperature){

	// Launch the thread
	temperatureThread = new std::thread(&TemperatureControl::temperatureTask, this);
}


TemperatureControl::~TemperatureControl()
{
	// Join and delete the thread
	temperatureThread->join();
	delete temperatureThread;

}


void TemperatureControl::temperatureTask() {

	HRC::time_point start, end;

	while (true) {

		// Get the current time
		start = HRC::now();

		// Trigger ADC to take temperature value
		this->simulator->triggerADCTemperature();

		// Read the current temperature value
		this->currentTemperature = this->simulator->readADCTemperature();

		// Turn on heater if the temperature is below C
		if (currentTemperature < this->C)
			this->simulator->switchHeater(true);
		// Turn off heater if above D
		else if (currentTemperature > this->D)
			this->simulator->switchHeater(false);

		end = HRC::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(temperaturePeriod - elapsedTime));
	}
}

double TemperatureControl::getCurrentTemperature() {
	return this->currentTemperature;
}