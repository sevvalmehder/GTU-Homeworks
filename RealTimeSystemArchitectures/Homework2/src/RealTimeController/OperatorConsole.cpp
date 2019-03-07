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

		// Create an empty string
		std::string output = "";

		// Get pressure value
		std::unique_lock<std::mutex> lockerP(pControl.mutexPressure);

		while(!pControl.isReaded) pControl.cv.wait(lockerP);

		pControl.isReaded = false;
		output += "Pressure: " + std::to_string(pControl.getCurrentPressure());
		lockerP.unlock();

		// Lock the system and wait for condition variable
		std::unique_lock<std::mutex> lockerT(tControl.mutexTemperature);
		while(!tControl.isReaded) tControl.cv.wait(lockerT);
		tControl.isReaded = false;
		output += ", Temperature :" + std::to_string(tControl.getCurrentTemperature());
		lockerT.unlock();

		// Display the current values
		std::cout << output  << std::endl;

		// Get current time
		end = HRC::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(consolePeriod - elapsedTime));

	}
	
}