.PHONY: all clean

CC=g++
CPP_STANDARD=c++14
LFLAGS= -std=$(CPP_STANDARD) -g 
CFLAGS=-c -std=$(CPP_STANDARD) -g

OBJS=grafo.o heuristicas.o common.o hamiltoniano.o

all: TP

TP: $(OBJS) tp.cpp
	$(CC) $(LFLAGS) $(OBJS) tp.cpp -o tp
grafo.o: grafo.h grafo.cpp
	$(CC) $(CFLAGS) grafo.cpp -o grafo.o
heuristicas.o: heuristicas.h heuristicas.cpp
	$(CC) $(CFLAGS) heuristicas.cpp -o heuristicas.o
hamiltoniano.o: hamiltoniano.h hamiltoniano.cpp
	$(CC) $(CFLAGS) hamiltoniano.cpp -o hamiltoniano.o
common.o: common.h common.cpp
	$(CC) $(CFLAGS) common.cpp -o common.o
clean: 
	rm *.o tp