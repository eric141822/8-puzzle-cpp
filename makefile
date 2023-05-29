all: main.out

CC:=g++
FLAGS = -Wall -pedantic-errors -O3 -std=c++17

main.out: state.o solver.o
	$(CC) $(FLAGS) -o main.out state.o solver.o
state.o: state.cpp state.hpp
	$(CC) $(FLAGS) -c state.cpp
solver.o: solver.cpp
	$(CC) $(FLAGS) -c solver.cpp

.PHONY: clean
clean:
	rm *.o main.out