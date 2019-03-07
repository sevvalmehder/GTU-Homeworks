#include "PressureControl.h"
#include <thread>
#include <mutex>

#define MILLISECOND 1000

std::mutex mutex;
using HRC = std::chrono::high_resolution_clock;

PressureControl::PressureControl(ISimulator* sim, int frequency, double initialPressure)
	:simulator(sim), pressurePeriod(MILLISECOND / frequency), currentPressure(initialPressure){

	// Not readed yet
	isReaded = false;

	// Launch a thread for pressure control
	pressureThread = new std::thread(&PressureControl::pressureTask, this);
	
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

		std::unique_lock<std::mutex> locker(mutexPressure);
		// Read the current pressure value to the currentPressure variable
		this->currentPressure = this->simulator->readADCPressure();
		isReaded = true;
		locker.unlock();
		cv.notify_one();

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