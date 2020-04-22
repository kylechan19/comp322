# Name: Kyle Chan
# Project: Lab 3: Catcher
CC=gcc
CFLAGS=-g -Wall -Wextra

all: catcher

catcher: catcher.c
	$(CC) $(CFLAGS) -c catcher.c
	$(CC) $(CFLAGS) -o $@ catcher.o -lm

clean:
	rm -f catcher catcher.o *~