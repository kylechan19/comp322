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
    if (argsLen < 1) { // Check argument length in child process
        printf("Not enough arguments CHILD.\n");
        _exit(EXIT_FAILURE);
    }
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
    else if (cpid1 == 0) { // First child, close stdout and replace with pipe, then execve
        // Set up new args for exec
        i = 0;
        for (j = 1; i < firstCmdLen; j++) {
            args1[i] = argv[j]; // Put args for child process
            i++;
        }
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        childrensPlay(args1, firstCmdLen); // Go execve()
    }
    else { // In parent
        fprintf(stderr, "CPID1: %d\n", cpid1); // Print first child pid
        // The parent closes access to pipe
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(cpid1, &childStatus, 0); // Wait for first child
        fprintf(stderr, "CPID1 Status: %d\n", childStatus); // Print first child status
        
        // Fork second child
        cpid2 = fork();
        if (cpid2 == -1) { // Err check
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (cpid2 == 0) { // Second child, close stdin and replace with pipe, then exec
            // Set up args for the second child
            if (secondCmdLen > 0) { // Check if second set of args was passed in
                i = 0;
                for (k = firstCmdLen+2; i < secondCmdLen; k++) {
                    args2[i] = argv[k]; // Put args for child process
                    i++;
                }
                dup2(pipefd[1], 2);
                close(pipefd[0]);
                childrensPlay(args2, secondCmdLen); // Go execve()
            }
            else {
                fprintf(stderr, "No arguments for child 2.\n");
            }
        }
        else { // Parent
            // The parent closes access to pipe
            close(pipefd[0]);
            close(pipefd[1]);
            fprintf(stderr, "CPID2: %d\n", cpid2); // Print second child pid
            waitpid(cpid2, &childStatus, 0); // Wait for second child
            fprintf(stderr, "CPID2 Status: %d\n", childStatus); // Print second child status
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
    printf("End of lab2.\n");
    return 0;
}