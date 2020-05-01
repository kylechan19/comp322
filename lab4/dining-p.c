/* Kyle Chan
    comp 322 - Prof. Benson
    Lab 4: Rice, Rice, and Rice
    20 April, 2020 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>   
#include <sys/stat.h>    
#include <semaphore.h>

static int seats;
static int position = 0;
sem_t * returnVal;
sem_t * chopstick[];

void useRandomRealTime() 
{
    int randNum;
    do {
        randNum = rand();
    } while (randNum > 1000000);
    usleep(randNum);
}

void eat()
{

}

void think()
{

}

int main(int argc, char *argv[])
{
    // Declare vars
    int pid;
    if (argc < 2)
        printf("Too few arguments.\n");
    else {
        seats = argv[1];
        position = argv[2];
        chopstick[seats-1];

        do {
            wait(chopstick[i]);
            wait(chopstick[(i+1) % ])
        } while (true);

    }
    fprintf(stderr, "End of lab4: dining-p.\n");
    return 0;
}