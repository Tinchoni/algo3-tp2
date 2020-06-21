.PHONY: all clean

CC=g++
CPP_STANDARD=c++14
LFLAGS= -std=$(CPP_STANDARD) -g 
CFLAGS=-c -pthread -std=$(CPP_STANDARD) -g

OBJS=grafo.o heuristicas.o common.o

all: TP

TP: $(OBJS) tp.cpp
	$(CC) $(LFLAGS) $(OBJS) tp.cpp -o tp
grafo.o: grafo.h grafo.cpp
	$(CC) $(CFLAGS) grafo.cpp -o grafo.o
heuristicas.o: heuristicas.h heuristicas.cpp
	$(CC) $(CFLAGS) heuristicas.cpp -o heuristicas.o
common.o: common.h common.cpp
	$(CC) $(CFLAGS) common.cpp -o common.o
clean: 
	rm *.o tp