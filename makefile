CC=g++
CFLAGS = -I. -Imodel/ -Wall -g -std=c++11

all:
	$(CC) Calculations.cpp main.cpp $(CFLAGS) -o triangulation

clean:
	rm -rf triangulation *.dSYM
