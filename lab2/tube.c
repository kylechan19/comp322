/* Kyle Chan
    Lab 2: Launch-Tube, tube.c
    Prof. Benson
    14 March, 2020 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void childrensPlay(int pipefd[], char* args[])
{
    dup2(pipefd[1], STDERR_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);

}

void forkin(char* argv[])
{
    // Declare vars
    int i, j, k, firstCmdLen, secondCmdLen;
    pid_t cpid1, cpid2;

    firstCmdLen = 0;
    secondCmdLen = 0;

    i = 1;
    while (argv[i] != "," && argv[i] != "\0") {
        firstCmdLen++;
        i++;
    }
    if (argv[i] == ",") {
        i = i+1;
        while (argv[i] != '\0') {
            secondCmdLen++;
            i++;
        }
    }

    char* args1[firstCmdLen], args2[secondCmdLen];

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
        /* Start reading from argv[1] into args1[i]. ex: tube /bin/cat filename , /usr/bin/head/ -2
            Stop reading once we hit the comma separation or we are only supplied one command. */
        i = 0;
        for (j = 1; i < firstCmdLen; j++) {
            args1[i] = argv[j]; // Put args for child process
            i++;
        }
        childrensPlay(pipefd, args1);
    }
    else { // Still in parent
        cpid2 = fork();
        if (cpid2 == -1) { // Err check
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (cpid2 == 0) { // In child2 proc.
            if (secondCmdLen > 0) { // Only do if supplied a second command
                /* Start reading from argv[j+1] to skip the comma and put value into into args1[i]. 
                    ex: tube /bin/cat filename , <- **(j is the COMMA!)** /usr/bin/head/ -2
                    Stop reading once we hit the end of argv. */
                i = 0;
                for (k = j+1; i < secondCmdLen; k++) {
                    args2[i] = argv[k]; // Put args for child process
                    i++;
                }
                childrensPlay(pipefd, args2);
            }
        }
        else { // Still in parent
            fprintf(stderr, "CPID 1: %d\nCPID 2: %d\n", cpid1, cpid2); // Print cpids to stderr
            fprintf(stderr, "s: %s\n", argv[1]);
            wait(NULL);
        }
    }
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("Not enough arguments.\n");
    }
    else
        forkin(argv);

    return 0;
}