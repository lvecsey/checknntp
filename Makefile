
CC=gcc

CFLAGS=-O3 -Wall -g -pg

checknntp : checknntp.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)
