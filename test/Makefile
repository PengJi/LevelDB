CC=gcc
CXX=g++ -std=c++11

CFLAGS = -Wall -O -g
LIB = -L../build
INC = -I../include
OBJS = file1.o file2.o

all: sample

sample: sample.cpp
	$(CXX) $(INC) $(LIB) -o $@ $< -lleveldb -lpthread -lsnappy

test: test.cpp
	$(CXX) $(INC) $(LIB) -o $@ $< -lleveldb -lpthread 

main: $(OBJS)
	$(CXX) $(OBJS) -o main

file1.o : file1.c file2.h
	$(CXX) $(CFLAGS) -c file1.c -o file1.o

file2.o : file2.c file2.h
	$(CXX) $(CFLAGS) -c file2.c -o file2.o

.PHONY: clean
clean:
	rm -rf *.o sample test
