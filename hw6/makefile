all: main

main: main.o SearchEngine.o Tire.o
	g++ main.o SearchEngine.o Tire.o -o hw6

main.o: main.cpp
	g++ -c main.cpp -o main.o

SearchEngine.o: SearchEngine.cpp
	g++ -c SearchEngine.cpp -o SearchEngine.o

Tire.o: Tire.cpp
	g++ -c Tire.cpp -o Tire.o

clean:
	rm -f *.o main