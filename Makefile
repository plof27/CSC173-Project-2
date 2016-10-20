CC=gcc
CFLAGS=-I.

makeLAW: main.o RDP.o TP.o ParseTree.o  helpers/LinkedList.o
	$(CC)  -o runMainLAW main.o RDP.o TP.o ParseTree.o  helpers/LinkedList.o -lm
#

# default: runMainLAW
# runMainLAW: main.o RDP.o TP.o ParseTree.o  helpers/LinkedList.o
# 	$(CC) $(CFLAGS) -o runMainLAW main.o RDP.o TP.o ParseTree.o  helpers/LinkedList.o
#
# main.o: main.c ParseTree.h RDP.h TP.h
# 	$(CC) $(CFLAGS) -c main.c
#
# RDP.o:RDP.c RDP.h
# 	$(CC) $(CFLAGS) -c RDP.c
#
# TP.o:TP.c TP.h
# 	$(CC) $(CFLAGS) -c TP.c
#
# ParseTree.o:ParseTree.c ParseTree.h
# 	$(CC) $(CFLAGS) -c ParseTree.c
#
# helpers/LinkedList.o:helpers/LinkedList.c helpers/LinkedList.h
# 	$(CC) $(CFLAGS) -c helpers/LinkedList.c
#
# 	RDP.h: RDP.h
# 		$(CC) $(CFLAGS) -c RDP.h
#
# 	TP.h: TP.h
# 		$(CC) $(CFLAGS) -c TP.h
#
# 	ParseTree.h: ParseTree.h
# 		$(CC) $(CFLAGS) -c ParseTree.h
#
# 	helpers/LinkedList.h: helpers/LinkedList.h
# 		$(CC) $(CFLAGS) -c helpers/LinkedList.h
