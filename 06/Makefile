CC = g++ -std=c++14

all: main run

main: main.o
	$(CC)   main.o -o  main

main.o: main.cpp
	$(CC) -c main.cpp 

clear:
	rm -rf *.o main

run:
	./main
