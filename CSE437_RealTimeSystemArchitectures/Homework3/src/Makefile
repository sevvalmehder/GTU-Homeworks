all: compile

compile: TestSimulator.o TemperatureControl.o PressureControl.o OperatorConsole.o main.o 
	g++ TestSimulator.o TemperatureControl.o PressureControl.o OperatorConsole.o main.o -o exe -lpthread

main.o: main.cpp
	g++ -c -std=c++11 main.cpp 

OperatorConsole.o: OperatorConsole.cpp
	g++ -c -std=c++11 OperatorConsole.cpp  

PressureControl.o: PressureControl.cpp
	g++ -c -std=c++11 PressureControl.cpp 

TemperatureControl.o: TemperatureControl.cpp
	g++ -c -std=c++11 TemperatureControl.cpp 

TestSimulator.o: TestSimulator.cpp
	g++ -c -std=c++11 TestSimulator.cpp 

clean:
	rm *.o exe
	clear

