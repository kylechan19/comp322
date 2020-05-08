# Name: Kyle Chan
# Project: Lab 6: Whack a Mole

CC=gcc
CFLAGS=-g -Wall -Wextra

all: spiritd moles

spiritd: spiritd.c
	$(CC) $(CFLAGS) -c spiritd.c
	$(CC) $(CFLAGS) -o $@ spiritd.o -lm

moles: mole.c
	$(CC) $(CFLAGS) -c mole.c
	$(CC) $(CFLAGS) -o moles mole.o -lm

clean:
	rm -f spirtd moles spiritd.o mole.o *~