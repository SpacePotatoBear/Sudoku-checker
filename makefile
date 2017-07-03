CC=gcc
CFLAGS=-Wall -pthread

checker: checker.c
	$(CC) $(CFLAGS) checker.c -o checker
