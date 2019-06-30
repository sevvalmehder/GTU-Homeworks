all: exe

exe: 151044009_HW3.o
	gcc 151044009_HW3.o -o withPipeandFIFO


151044009_HW3.o: 151044009_HW3.c
	gcc -c -ansi -pedantic-errors 151044009_HW3.c -Wall

clean:
	rm *.o withPipeandFIFO
	clear 
