CC=g++

all: test

test: test_
	./test_

run: test

test_: main.cpp
	$(CC) -o test_ main.cpp -O2 --std=c++14

clear:
	rm -rf *.o test_