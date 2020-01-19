CC = g++ -std=c++14

all: create sort test

test: test.o
	$(CC)   test.o -o  test
	./test

test.o: test.cpp
	$(CC) -c test.cpp 

create: create.o
	$(CC)   create.o -o  create
	./create

create.o: create.cpp
	$(CC) -c create.cpp 


sort: %: %.cpp
	$(CC) $< -o $@ -pthread
	./sort

clear: 
	rm -rf *.o test	
	rm -rf *.o create
	rm -rf *.o sort