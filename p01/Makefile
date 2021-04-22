CXX=g++
CXXFLAGS=-std=c++17 -O2 -Wall -g

build: cli.o varlenString.o plane.o database.o
	$(CXX) $(CXXFLAGS) cli.o varlenString.o plane.o database.o -o cli

test: test.o varlenString.o plane.o
	$(CXX) $(CXXFLAGS) test.o varlenString.o plane.o -o test
	./test

clean:
	rm $(wildcard *.o)

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o
cli.o: cli.cpp
	$(CXX) $(CXXFLAGS) -c cli.cpp -o cli.o
varlenString.o: varlenString.cpp
	$(CXX) $(CXXFLAGS) -c varlenString.cpp -o varlenString.o
plane.o: plane.cpp
	$(CXX) $(CXXFLAGS) -c plane.cpp -o plane.o
database.o: database.cpp
	$(CXX) $(CXXFLAGS) -c database.cpp -o database.o
