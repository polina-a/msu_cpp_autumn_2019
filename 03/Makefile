CC=g++

all: matrix run

matrix: matrix.o main.o
	$(CC) matrix.o  main.o -o  matrix

matrix.o: matrix.cpp 
	$(CC) -c matrix.cpp

main.o: main.cpp
	$(CC) -c main.cpp 

clear:
	rm -rf *.o matrix

run:
	./matrix
