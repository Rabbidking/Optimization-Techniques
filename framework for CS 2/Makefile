CXX=g++ -O0
PROGS=..
CXXFLAGS=-Wall -g  -I/usr/include/SDL2 
LDFLAGS=-lGL -lSDL2 -lpng -lz -lturbojpeg -ldl

all: main.o glfuncs.o miniz_tinfl.o statics.o
	$(CXX) main.o glfuncs.o statics.o miniz_tinfl.o -o main $(LDFLAGS)	
	
miniz_tinfl.o: 
	$(CXX) -c miniz_tinfl.c
	
glfuncs.o: 
	$(CXX) -c glfuncs.cpp 

statics.o: statics.cpp
	$(CXX) -c $(CXXFLAGS) statics.cpp
	
main.o: main.cpp $(wildcard *.h)
	$(CXX) -c $(CXXFLAGS) main.cpp 

clean: 
	-/bin/rm *.o main

zip:
	-/bin/rm framework.zip
	zip framework.zip *.cpp *.h *.png *.txt shaders/*.txt *.obj *.c Makefile
