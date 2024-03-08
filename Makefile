CC = gcc
CFLAGS = -g -Wall -Wshadow
scanner: scanner.o
	$(CC) $(CFLAGS) -v scanner.o -o scanner
scanner.o: scanner.c scanner.h langscan.h ttoken.h
	$(CC) $(CFLAGS) -c scanner.c scanner.h langscan.h ttoken.h
.PHONY: clean
clean:
	rm *.o scanner *.gch
