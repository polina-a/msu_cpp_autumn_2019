CC=g++

all: my_prog1 my_prog2 run

my_prog1: sum_by_rows.o 
	$(CC) sum_by_rows.o -o my_prog1
my_prog2: sum_by_cols.o
	$(CC) sum_by_cols.o -o my_prog2	
sum_by_rows.o: sum_by_rows.cpp
	$(CC) -c sum_by_rows.cpp
sum_by_cols.o: sum_by_cols.cpp
	$(CC) -c sum_by_cols.cpp	
clean:
	rm -rf *.o my_prog1 my_prog2
run: 
	./my_prog1
	./my_prog2
	