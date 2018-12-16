#include <thread>
#include <iostream>
#include "TestSimulator.h"
#include "PressureControl.h"
#include "TemperatureControl.h"
#include "OperatorConsole.h"

// Period values of tasks in Hertz
#define PRESSURE_FREQ 10
#define TEMPERATURE_FREQ 3
#define	CONSOLE_FREQ 2

using HRC = std::chrono::high_resolution_clock;

int main() {

	// Change this values for different test cases
	double initialP = 0.02;
	double initialT = 37;
	int executionTime = 10; // in second

	HRC::time_point start, end;
	auto elapsedTime = 0;

	start = HRC::now();

	// Create simulator object
	ISimulator *simulator = new TestSimulator(initialP, initialT);

	// Create pressure object
	// Send simulator and period()
	PressureControl p_control(simulator, PRESSURE_FREQ, initialP);

	// Create temperature object
	TemperatureControl t_control(simulator, TEMPERATURE_FREQ, initialT);

	// Create console operator object
	OperatorConsole o_control(CONSOLE_FREQ, p_control, t_control);

	// Run until given executionTime end
	while (true) {
		end = HRC::now();
		elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

		if (elapsedTime >= executionTime)
			exit(1);

	}

}


