CC = g++
CFLAGS = -std=c++11

all: PhonePricePrediction.out

PhonePricePrediction.out: main.o tools.o
	g++ main.o tools.o -o PhonePricePrediction.out

main.o: main.cpp tools.h
	$(CC) $(CFLAGS) -c main.cpp  -o main.o

tools.o: tools.cpp tools.h 
	$(CC) $(CFLAGS) -c tools.cpp -o tools.o

clean:
	rm *.o
	rm *.out