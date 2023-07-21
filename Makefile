CC = gcc
CFLAGS = -Wall 

all: main

main: ticTacToe.c ticTacToe.o
	$(CC) $(CFLAGS) ticTacToe.c -o ticTacToe.exe