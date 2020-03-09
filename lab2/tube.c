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
    int pid = getpid();
    if (argsLen < 2) {
        printf("Not enough arguments CHILD.\n");
        exit(EXIT_FAILURE);
    }
    printf("CPID: %d, execve\n", pid);
    execve(args[0], args, NULL); // Execute proc.
    perror("execve failed");
}

void forkin(char* argv[], int argc)
{
    // Declare vars
    int i, j, k, firstCmdLen, secondCmdLen, childStatus;
    pid_t cpid1, cpid2;

    // Init. because compiler complains
    firstCmdLen = 0;
    secondCmdLen = 0;
    j = 0;

    /* This loop is set up for the first set of args and stops if we only receive one cmd,
        or if we hit the comma separator from the usage examples. */
    for (i = 1; i < argc; i++) {
        //printf("HI FROM LOOP 1\n");
        if (*argv[i] == '\0' || *argv[i] == ',')
            break;
        //printf("Loop 1 argv[i]: %s\n", argv[i]);
        firstCmdLen++;
    }
    //printf("firstCmdLen: %d\n", firstCmdLen);

    /* This loop is set up for the second set of args and stops if we reach the null terminator.
        Checks if it did in fact receive two commands by looking for the comma separator. */
    if (*argv[i] == ',') {
        for (i = i+1; i < argc; i++) {
            //printf("HI FROM LOOP 2\n");
            if (*argv[i] == '\0')
                break;
            //printf("Loop 2 argv[i]: %s\n", argv[i]);
            secondCmdLen++;
        }
    }
    //printf("secondCmdLen: %d\n", secondCmdLen);

    // args for child processes
    char* args1[firstCmdLen+1];
    char* args2[secondCmdLen+1];
    // MUST END WITH NULL TERMINATOR
    args1[firstCmdLen] = (char*)0;
    args1[secondCmdLen] = (char*)0;

    // PIPE STUFF
    int pipefd1[2];
    if (pipe(pipefd1) == -1) { // Allocate pipe, Err check
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int pipefd2[2];
    if (pipe(pipefd2) == -1) { // Allocate pipe, Err check
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    cpid1 = fork(); // First fork
    if (cpid1 == -1) {// Err check
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (cpid1 == 0) { // First child, close stdout and replace with pipe, then execve
        // Set up new args for exec
        i = 0;
        for (j = 1; i < firstCmdLen; j++) {
            //printf("HI FROM LOOP 3\n");
            args1[i] = argv[j]; // Put args for child process
            //printf("Loop 3 args1[%d]: %s\n", i, args1[i]);
            //printf("Loop 3 argv[%d]: %s\n", j, argv[j]);
            i++;
        }
        //printf("Loop 3 args1[firstCmdLen:%d]: %s\n", firstCmdLen, args1[firstCmdLen]);

        // Go execve after pipe stuff
        dup2(pipefd1[1], 2); // writer reads from stdin (pipe) and writes to stderr
        close(pipefd1[1]);
        childrensPlay(args1, firstCmdLen);
    }
    else { // In parent
        cpid2 = fork();
        if (cpid2 == -1) { // Err check
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (cpid2 == 0) { // Second child, close stdin and replace with pipe, then exec
            // Set up args for the second child
            i = 0;
            for (k = firstCmdLen+2; i < secondCmdLen; k++) {
                //printf("HI FROM LOOP 4\n");
                args2[i] = argv[k]; // Put args for child process
                //printf("Loop 4 args2[%d]: %s\n", i, args2[i]);
                //printf("Loop 4 argv[%d]: %s\n", k, argv[k]);
                i++;
            }
            //printf("Loop 4 args2[secondCmdLen:%d]: %s\n", secondCmdLen, args2[secondCmdLen]);
            // Go execve after pipe stuff
            dup2(pipefd2[1], 2); //reader reads from stdout
            close(pipefd2[1]);
            childrensPlay(args2, secondCmdLen);
        }
        else { // Parent
            // The parent closes both ends of the pipes
            close(pipefd1[0]);
            close(pipefd1[1]);
            close(pipefd2[0]);
            close(pipefd2[1]);

            fprintf(stderr, "CPID1: %d\n", cpid1);
            waitpid(cpid1, &childStatus, 0); // Wait for first child
            fprintf(stderr, "CPID1 Status: %d\n", childStatus);

            fprintf(stderr, "CPID2: %d\n", cpid2);
            waitpid(cpid2, &childStatus, 0); // Wait for second child
            fprintf(stderr, "CPID2 Status: %d\n", childStatus);
        }
    }
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("Not enough arguments MAIN.\n");
    }
    else {
        forkin(argv, argc);
    }
    return 0;
}