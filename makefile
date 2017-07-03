CC=clang
CFLAGS=-Wall

checker: checker.c
	$(CC) $(CFLAGS) checker.c -o checker
