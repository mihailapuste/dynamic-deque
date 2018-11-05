all: main

main: main.o Deque.o
	g++ -o main main.o Deque.o

main.o: main.cpp Deque.o Deque.h
	g++ -c main.cpp

Deque.o: Deque.cpp Deque.h
	g++ -c Deque.cpp

clean:
	rm -f main *.o
