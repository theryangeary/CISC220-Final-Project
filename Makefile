#CXX = g++
CXXFLAGS = -O2 -std=c++11

LIBS =
LDLIBS =
INCLUDES =

# force clean build every time
all: clean main

main: Graph.o main.o
	$(CXX) $^ -o $@

# name a variable cources for all source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	rm -f *.o
	rm -f *.exe

