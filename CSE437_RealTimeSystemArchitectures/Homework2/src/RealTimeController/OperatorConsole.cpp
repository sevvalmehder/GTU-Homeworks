#include <iostream>
#include <string>
#include "ISimulator.h"
#include "OperatorConsole.h"

using HRC = std::chrono::high_resolution_clock;

OperatorConsole::OperatorConsole(int frequency, PressureControl& pressureRef, TemperatureControl& temperatureRef)
	:consolePeriod(1 / frequency), pControl(pressureRef), tControl(temperatureRef) {

	// Launch the thread
	consoleThread = new std::thread(&OperatorConsole::consoleTask, this);
}


OperatorConsole::~OperatorConsole()
{
	// Join and delete the thread
	consoleThread->join();
	delete consoleThread;
}


void OperatorConsole::consoleTask() {

	HRC::time_point start, end;

	while (true) {

		// Get current time
		start = HRC::now();

		std::cout << "Pressure: " << pControl.getCurrentPressure() << ", Temperature :" << tControl.getCurrentTemperature() << std::endl;

		// Get current time
		end = HRC::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(start - end).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(consolePeriod - elapsedTime));

	}
	
}