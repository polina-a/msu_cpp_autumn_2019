CC = g++ -std=c++14

all: test run

test: test.o
	$(CC)   test.o -o  test

test.o: test.cpp
	$(CC) -c test.cpp 

clear:
	rm -rf *.o test

run:
	./test
