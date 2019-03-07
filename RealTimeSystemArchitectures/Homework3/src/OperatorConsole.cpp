#include <iostream>
#include <string>
#include "ISimulator.h"
#include "OperatorConsole.h"

#define MILLISECOND 1000

using HRC = std::chrono::high_resolution_clock;

OperatorConsole::OperatorConsole(int frequency, PressureControl& pressureRef, TemperatureControl& temperatureRef)
	:consolePeriod(MILLISECOND / frequency), pControl(pressureRef), tControl(temperatureRef) {

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

	HRC::time_point start, end, deadlineControlTime;

	// The time between deadline control time and last updated time
	int pressureDiff, temperatureDiff;

	// Deadline miss control variables
	bool pressDeadlineMiss, tempDeadlineMiss;

	while (true) {

		// Get current time
		start = HRC::now();

		// Deadline miss control
		pressDeadlineMiss = false;
		tempDeadlineMiss = false;

		// Control deadline miss for every 10 ms
		// Write pressure and temperature value for every 500 ms
		// We can check dedline miss for 50 times
		int deadlineMissCount = 50;
		while(deadlineMissCount){

			// Get the beginning of control time
			deadlineControlTime = HRC::now();
			// Calculate the time between deadline control time and pressure last updated time
			pressureDiff = std::chrono::duration_cast<std::chrono::milliseconds>(deadlineControlTime - pControl.pressureLastUpd).count();
			// If the time longer than pressure period warning about deadline miss
			if(pressureDiff > pControl.pressurePeriod && !pressDeadlineMiss){
				std::cout << "WARNING! Pressure Controller deadline miss by " << pressureDiff - pControl.pressurePeriod << " milliseconds" << std::endl;
				pressDeadlineMiss = true;
			}

			// Calculate the time between deadline control time and temperature last updated time
			temperatureDiff = std::chrono::duration_cast<std::chrono::milliseconds>(deadlineControlTime - tControl.tempLastUpd).count();
			// If the time longer than temperature period warning about deadline miss
			if(temperatureDiff > tControl.temperaturePeriod && !tempDeadlineMiss){
				std::cout << "WARNING! Temperature Controller deadline miss by " << temperatureDiff - tControl.temperaturePeriod << " milliseconds" << std::endl;
				tempDeadlineMiss = true;
			}

			--deadlineMissCount;
		}
		// When deadline miss control ends, time to write console ouput
		// Create an empty string
		std::string output = "";

		// Get pressure value
		output += "Pressure: " + std::to_string(pControl.getCurrentPressure());

		output += ", Temperature :" + std::to_string(tControl.getCurrentTemperature());

		// Display the current values
		std::cout << output  << std::endl;

		// Get current time
		end = HRC::now();

		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::this_thread::sleep_for(std::chrono::milliseconds(consolePeriod - elapsedTime));

	}
	
}