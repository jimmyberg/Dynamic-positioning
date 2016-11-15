FILEOUT = dynpos
FILES = main.cpp PIDController.cpp
PARAM = -std=c++11 -O0

all:
	g++ $(PARAM) -o $(FILEOUT) $(FILES)

