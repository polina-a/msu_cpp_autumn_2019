CC=g++

all: bigint run

bigint: bigint.o main.o
	$(CC) bigint.o  main.o -o  bigint

bigint.o: bigint.cpp 
	$(CC) -c bigint.cpp

main.o: main.cpp
	$(CC) -c main.cpp 

clear:
	rm -rf *.o bigint

run:
	./bigint
