CC=gcc
CFLAGS=-I.

LAWmake: main.o NFA.o LinkedList.o DFA.o
	$(CC) -o project1 main.o NFA.o LinkedList.o DFA.o -I.
