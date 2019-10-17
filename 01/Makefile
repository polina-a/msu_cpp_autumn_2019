CC=g++

all: calc test

calc: calc.o
	$(CC) calc.o -o  calc

calc.o: calc.cpp
	$(CC) -c calc.cpp

clear:
	rm -rf *.o calc
run:
	./calc

test: calc
	python3 ./test.py

