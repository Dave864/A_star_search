CPP = g++
CFLAGS= -Wall -g
DEBUGGER= -ggdb

SRCS= Problem.cpp

a_star: A_star.cpp Problem.o
	$(CPP) $(CFLAGS) $(DEBUGGER) -o a_star A_star.cpp Problem.o

Problem.o: Problem.cpp Problem.h
	$(CPP) $(CFLAGS) $(DEBUGGER) -c Problem.cpp

clean:
	rm *.o a_star -f
