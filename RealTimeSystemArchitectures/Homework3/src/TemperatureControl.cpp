#include "TemperatureControl.h"


#define MILLISECOND 1000

using HRC = std::chrono::high_resolution_clock;

TemperatureControl::TemperatureControl(ISimulator* sim, int frequency, double initialTemperature)
	:simulator(sim), temperaturePeriod( MILLISECOND / frequency), currentTemperature(initialTemperature), tempLastUpd(HRC::now()){


	// Launch the thread
	temperatureThread = new std::thread(&TemperatureControl::temperatureTask, this);

	// Set priority for thread
	// Run at real time priority level 10
	setPriority(SCHED_RR, 10);

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
		tempLastUpd = HRC::now();

		// Turn on heater if the temperature is below C
		if (currentTemperature <= this->C)
			this->simulator->switchHeater(true);
		// Turn off heater if above D
		else if (currentTemperature >= this->D)
			this->simulator->switchHeater(false);

		end = HRC::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(temperaturePeriod - elapsedTime));
	}
}

double TemperatureControl::getCurrentTemperature() {
	return this->currentTemperature;
}

void TemperatureControl::setPriority(int policy, int priority){

	// store the scheduling priortiy
	sched_param scParams;


	scParams.sched_priority = priority;

	// get phtread object
	auto pthreadObj = temperatureThread->native_handle();

	// Attempt to set thread real-time priority to the given policy
	int ret = pthread_setschedparam(pthreadObj, policy, &scParams);
	if (ret) {
		// Print the error
		std::cerr << "Unsuccessful in setting thread realtime priority" << std::endl;
		return;     
	}

}