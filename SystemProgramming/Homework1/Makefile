all: exe

exe: 151044009_SevvalMehder.o
	gcc 151044009_SevvalMehder.o -o list


151044009_SevvalMehder.o: 151044009_SevvalMehder.c
	gcc -c -ansi -pedantic-errors 151044009_SevvalMehder.c -Wall

clean:
	rm *.o list
