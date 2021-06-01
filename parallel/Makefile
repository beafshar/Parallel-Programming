CC = g++
CFLAGS = -std=c++11
LINK_FLAGS = -I $(INCLUDE_DIR) -I $(INLINE_DIR) -pthread

all: PhonePricePrediction.out

PhonePricePrediction.out: main.o tools.o
	$(CC) $(CFLAGS) $(LINK_FLAGS) main.o tools.o -o PhonePricePrediction.out

main.o: main.cpp tools.h
	$(CC) $(CFLAGS) -c main.cpp  -o main.o

tools.o: tools.cpp tools.h 
	$(CC) $(CFLAGS) -c tools.cpp -o tools.o

clean:
	rm *.o
	rm *.out