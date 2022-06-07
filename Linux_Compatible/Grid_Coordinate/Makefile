CPP=g++
LDFLAGS=-lglut -lGLU -lGL

.PHONY: clean

all:Grid_Coordinate.exe

Grid_Coordinate.exe: Grid_Coordinate.cpp
	$(CPP) $< -o $@ $(LDFLAGS)

test: lab3
	./lab3

clean:
	rm -rf Grid_Coordinate.exe

