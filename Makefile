CPP = g++

make: main.cpp
	$(CPP) -o main main.cpp
	./main