# Name: Kyle Chan
# Project: Lab 4: Rice, Rice, and Rice
CC=gcc
CFLAGS=-g -Wall -Wextra

all: dining-p

dining-p: dining-p.c
	$(CC) $(CFLAGS) -c dining-p.c
	$(CC) $(CFLAGS) -o $@ dining-p.o -lm -lpthread

clean:
	rm -f dining-p dining-p.o *~