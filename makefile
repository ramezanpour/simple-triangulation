CC=g++
CFLAGS = -I. -Imodel/ -Wall -g -std=c++11

all:
	$(CC) Calculations.cpp main.cpp $(CFLAGS) -o trianglation

clean:
	rm -rf trianglation *.dSYM


