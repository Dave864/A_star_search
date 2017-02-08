CPP = g++
CFLAGS= -Wall -g
DEBUGGER= -ggdb

SRCS= Problem.cpp

a_star: A_star.cpp Problem.o
	$(CPP) $(CFLAGS) -o a_star A_star.cpp Problem.o

Problem.o: Problem.cpp Problem.h
	$(CPP) $(CFLAGS) -c Problem.cpp

clean:
	rm *.o a_star -f
