# Name: Kyle Chan
# Project: Lab 0: Making Sense of 1's and 0's

CC=gcc
CFLAGS=-g -Wall -Wextra

all: lab0

lab0: lab0.c
	$(CC) $(CFLAGS) -c lab0.c
	$(CC) $(CFLAGS) -o $@ lab0.o -lm

clean:
	rm -f lab0 lab0.o *~