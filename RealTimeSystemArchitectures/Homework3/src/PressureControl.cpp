#include "PressureControl.h"
#include <thread>

#define MILLISECOND 1000

using HRC = std::chrono::high_resolution_clock;

PressureControl::PressureControl(ISimulator* sim, int frequency, double initialPressure)
	:simulator(sim), pressurePeriod(MILLISECOND / frequency), currentPressure(initialPressure), pressureLastUpd(HRC::now()){

	// Launch a thread for pressure control
	pressureThread = new std::thread(&PressureControl::pressureTask, this);
	
	// Set priority for thread
	// Run at real time priority level 10
	setPriority(SCHED_RR, 10);
}


PressureControl::~PressureControl()
{
	// Join and delete the thread
	pressureThread->join();
	delete pressureThread;

}

void PressureControl::pressureTask() {

	double u;
	HRC::time_point start, end;

	while (true) {
		// Get current time 
		start = HRC::now();

		// Trigger ADC to take pressure value
		this->simulator->triggerADCPressure();

		// Read the current pressure value to the currentPressure variable
		this->currentPressure = this->simulator->readADCPressure();
		pressureLastUpd = HRC::now();

		// Control operation
		if (this->currentPressure < 0.9)
			u = A - B * this->currentPressure;
		else
			u = 0;

		// Write this value to DAC
		this->simulator->writeDACPump(u);

		// Get current time
		end = HRC::now();

		// Calculate the elapsed time and sleep for period-elapsedTime
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::this_thread::sleep_for( std::chrono::milliseconds(pressurePeriod - elapsedTime));
		
	}


}

double PressureControl::getCurrentPressure() {
	return this->currentPressure;
}

void PressureControl::setPriority(int policy, int priority){

	// store the scheduling priortiy
	sched_param scParams;


	scParams.sched_priority = priority;

	// get phtread object
	auto pthreadObj = pressureThread->native_handle();

	// Attempt to set thread real-time priority to the given policy
	int ret = pthread_setschedparam(pthreadObj, policy, &scParams);
	if (ret) {
		// Print the error
		std::cerr << "Unsuccessful in setting thread realtime priority" << std::endl;
		return;     
	}

}