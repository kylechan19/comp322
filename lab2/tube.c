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

void childrensPlay(int pipefd[], char* args[], int argsLen)
{
    if (argsLen < 2) {
        printf("Not enough arguments.\n");
        _exit(EXIT_SUCCESS);
    }
    // Declare vars
    char* actualArgs[argsLen-1];
    char* filename = args[0];
    int i, j;

    // Set up the arguments for child process
    j = 0;
    for (i = 0; i < argsLen; i++) {
        actualArgs[j] = args[i];
        j++;
    }

    dup2(pipefd[1], STDERR_FILENO);
    close(pipefd[0]);
    close(pipefd[1]);
    execve(filename, actualArgs, NULL);
    _exit(EXIT_SUCCESS);
}

void forkin(char* argv[], int argc)
{
    // Declare vars
    int i, j, k, firstCmdLen, secondCmdLen, nbytes;
    //childOneStatus, childTwoStatus;
    pid_t cpid1, cpid2;
    char output[32768];

    firstCmdLen = 0;
    secondCmdLen = 0;
    // childOneStatus = 0;
    // childTwoStatus = 0;
    j = 0;

    /* This loop sets up the first set of args and stops if we only receive one cmd,
        or if we hit the comma separator from the usage examples. */
    for (i = 1; i < argc; i++) {
        //printf("HI FROM LOOP 1\n");
        if (*argv[i] == ',' || *argv[i] == '\0')
            break;
        firstCmdLen++;
    }
    /* This loop sets up the second set of args and stops if we reach the null terminator.
        Checks if it did in fact receive more than one command by looking for the comma separator. */
    if (*argv[i] == ',') {
        for (i = i+1; i < argc; i++) {
            //printf("HI FROM LOOP 2\n");
            if (*argv[i] == '\0')
                break;
            secondCmdLen++;
        }
    }

    // args for child processes
    char* args1[firstCmdLen];
    char* args2[secondCmdLen];

    // PIPE STUFF
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

    if (cpid1 > 0) { // In parent
        cpid2 = fork(); // Fork again (Create second child)
        if (cpid2 == -1) { // Err check
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (cpid2 > 0) { // In parent still
            fprintf(stderr, "CPID 1: %d\nCPID 2: %d\n", cpid1, cpid2); // Print cpids to stderr
            close(pipefd[1]);
            nbytes = read(pipefd[0], output, sizeof(output));
            printf("%.*s\n", nbytes, output);
            wait(NULL);
            //wait(&childOneStatus);
            //wait(&childTwoStatus);
            //fprintf(stderr, "CPID 1 Status: %d\nCPID 2 Status: %d\n", childOneStatus, childTwoStatus); // Print cpids to stderr
        }

        if (cpid2 == 0) { // In second child proc.
            if (secondCmdLen > 0) { // Only do if supplied a second command
                // Set up args for the second child
                i = 0;
                for (k = j; i < secondCmdLen; k++) {
                    //printf("HI FROM LOOP 3\n");
                    args2[i] = argv[k]; // Put args for child process
                    i++;
                }
                childrensPlay(pipefd, args2, secondCmdLen);
            }
        }
    }
    if (cpid1 == 0) { // In first child proc.
        /* Start reading from argv[1] into args1[i]. ex: tube /bin/cat filename , /usr/bin/head/ -2
            Stop reading once we hit the comma separation or we are only supplied one command. */
        i = 0;
        for (j = 0; i < firstCmdLen; j++) {
            //printf("HI FROM LOOP 4\n");
            args1[i] = argv[j]; // Put args for child process
            i++;
        }
        childrensPlay(pipefd, args1, firstCmdLen);
    }
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("Not enough arguments.\n");
    }
    else {
        forkin(argv, argc);
    }
    return 0;
}