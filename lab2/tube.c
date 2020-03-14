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

void childrensPlay(char* args[], int argsLen)
{
    if (argsLen > 0) { // Check argument length in child process
        execve(args[0], args, NULL); // Execute proc.
        perror("execve failed");
        
    }
    else {
        printf("Not enough arguments CHILD.\n");
        _exit(EXIT_FAILURE);
    }
}

void forkin(char* args1[], int argsLen, int pipefd[])
{
    pid_t cpid1;
    switch (cpid1 = fork()) { // First fork
        case -1: // ERROR first child
            perror("fork");
            exit(EXIT_FAILURE);
        default: // Parent
            break;
        case 0: // First child
            if (argsLen > 0) {
                dup2(pipefd[1], 1); // Change stdout to write end of pipe
                close(pipefd[0]); // Close unneeded read end of pipe in THIS CHILD
                childrensPlay(args1, argsLen); // Go execve()
            }
            else {
                fprintf(stderr, "Not enough arguments PID: %d\n", getpid());
                _exit(EXIT_FAILURE);
            }
    }
}

void forkinAgain(char* args2[], int argsLen, int pipefd[]) 
{
    pid_t cpid2;
    switch (cpid2 = fork()) { // Second fork
        case -1: // ERROR Second child
            perror("fork");
            exit(EXIT_FAILURE);
        default: // Parent
            break;
        case 0: // second child
            if (argsLen > 0) {
                dup2(pipefd[0], 0); // Change stdin to read end of pipe
                close(pipefd[1]); // Close unneeded write end of pipe in THIS CHILD
                childrensPlay(args2, argsLen); // Go execve()
            } 
            else {
                fprintf(stderr, "Not enough arguments PID: %d\n", getpid());
                _exit(EXIT_FAILURE);
            }
    }
}

int main(int argc, char *argv[]) 
{
    // Declare vars
    int i, j, k, firstCmdLen, secondCmdLen, childStatus, cpid;
    int pipefd[2];

    // Init. These values need to be 0 by default, in case not enough args are passed in
    firstCmdLen = 0;
    secondCmdLen = 0;

    /* This loop is set up for the first set of args and stops if we only receive one cmd,
        or if we hit the comma separator from the usage examples. */
    for (i = 1; i < argc; i++) {
        if (*argv[i] == ',')
            break;
        firstCmdLen++;
    }

    /* This loop is set up for the second set of args and stops if we reach the null terminator.
        Checks if it did in fact receive two commands by looking at the value of i after
        the previous loop finishes. */
    if (argv[i] != argv[argc]) {
        for (i = i+1; i < argc; i++) {
            if (*argv[i] == '\0')
                break;
            secondCmdLen++;
        }
    }

    // args for child processes
    char* args1[firstCmdLen+1];
    char* args2[secondCmdLen+1];
    // MUST END WITH NULL TERMINATOR
    args1[firstCmdLen] = (char*)0;
    args2[secondCmdLen] = (char*)0;

    // Set up new args for first child
    if (firstCmdLen > 0) {
        i = 0;
        for (j = 1; i < firstCmdLen; j++) {
            args1[i] = argv[j]; // Put args for child process
                i++;
            }
    }
    else {
        fprintf(stderr, "Not enough arguments for the first child.\n");
    }

    // Set up args for the second child
    if (secondCmdLen > 0) {
        i = 0;
        for (k = firstCmdLen+2; i < secondCmdLen; k++) { // k = that value to skip argv[0] and ','
            args2[i] = argv[k]; // Put args for child process
            i++;
        }
    }
    else {
        fprintf(stderr, "Not enough arguments for second child.\n");
    }

    // The juicy part of the program
    if (argc < 2) {
        printf("Not enough arguments MAIN.\n");
    }
    else {
        pipe(pipefd); // Allocate pipe
        forkin(args1, firstCmdLen, pipefd); // Fork first child
        forkinAgain(args2, secondCmdLen, pipefd); // Fork second child
        close(pipefd[0]); // The parent closes BOTH ends of the pipe
        close(pipefd[1]);
        while ((cpid = wait(&childStatus)) != -1) // Parent waits for children to finish
		    fprintf(stderr, "PID: %d\nStatus: %d\n", cpid, WEXITSTATUS(childStatus)); // print pid and retval of child
    }
    fprintf(stderr, "End of lab2-tube.\n");
    return 0;
}