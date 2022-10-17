polygon : main.o algorithms.o
	g++ main.o algorithms.o -o polygon

main.o : main.cpp headers.h 
	g++ -c main.cpp

algorithms.o : algorithms.cpp headers.h
	g++ -c algorithms.cpp

clean:
	rm polygon main.o algorithms.o
