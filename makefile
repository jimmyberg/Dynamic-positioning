CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
LINKFLAGS=-pthread
BIN=prog

SRC=$(wildcard *.cpp) $(wildcard */*.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) $(LINKFLAGS) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o */*.o
	rm $(BIN)
