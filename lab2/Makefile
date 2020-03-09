# Name: Kyle Chan
# Project: Lab 2: Launch-Tube

CC=gcc
CFLAGS=-g -Wall -Wextra

all: launch tube

launch: launch.c
	$(CC) $(CFLAGS) -c launch.c
	$(CC) $(CFLAGS) -o $@ launch.o -lm

tube: tube.c
	$(CC) $(CFLAGS) -c tube.c
	$(CC) $(CFLAGS) -o $@ tube.o -lm

clean:
	rm -f launch tube launch.o tube.o *~