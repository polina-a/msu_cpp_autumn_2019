CC=g++

all: allocator run

allocator: allocator.o
	$(CC) allocator.o -o  allocator

allocator.o: allocator.cpp
	$(CC) -c allocator.cpp

clear:
	rm -rf *.o allocator
run:
	./allocator


	
