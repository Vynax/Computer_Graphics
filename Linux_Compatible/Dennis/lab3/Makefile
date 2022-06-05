CPP=g++
LDFLAGS=-lglut -lGLU -lGL

.PHONY: clean

all:lab3

lab3: lab3.cpp
	$(CPP) $< -o $@ $(LDFLAGS)

test: lab3
	./lab3

clean:
	rm -rf lab2

