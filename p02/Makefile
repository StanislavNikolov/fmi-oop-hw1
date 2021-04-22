CXX=c++
CXXFLAGS=-std=c++17 -O2 -Wall
build: cli.o
	$(CXX) $(CXXFLAGS) cli.o -o cli -Llibbcrypt/build -lbcrypt

clean:
	rm $(wildcard *.o)

cli.o: cli.cpp
	$(CXX) $(CXXFLAGS) cli.cpp -c -o cli.o -Ilibbcrypt/include

