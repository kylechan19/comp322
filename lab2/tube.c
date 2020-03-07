/* Kyle Chan
    Lab 2: Launch-Tube, tube.c
    Prof. Benson
    17 March, 2020 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void childrensPlay()
{
    char buf;
    close(1);
    while (read(0, &buf, 1) > 0)
        write(STDOUT_FILENO, &buf, 1);
    write(STDOUT_FILENO, "\n", 1);
    close(0);
    _exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) 
{
    // Declare vars
    pid_t cpid1, cpid2;

    if (argc < 2) {
        printf("Not enough arguments");
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) { // Allocate pipe, Err check
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    cpid1 = fork(); // First fork
    if (cpid1 == -1) {// Err check
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    if (cpid1 == 0) { // In child1 proc.
        childrensPlay();
    }
    else { // Still in parent
        cpid2 = fork();
        if (cpid2 == -1) { // Err check
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (cpid2 == 0) { // In child2 proc.
            childrensPlay();
        }
        else { // Still in parent
            fprintf(stderr, "CPID 1: %d\nCPID 2: %d", cpid1, cpid2); // Print cpids to stderr
            
        }
    }

    return 0;
}