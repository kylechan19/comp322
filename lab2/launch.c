/* Kyle Chan
    Lab 2: Launch-Tube, launch.c
    Prof. Benson
    17 March, 2020 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void childsPlay(int argc, char *argv[]) 
{
    // Prepare new argv
    int i;
    char *argvChild[argc];

    for (i = 2; i < argc; i++) {
        argvChild[i] = argv[i]; // Put args for child process
    }
    // Child executes with supplied commands
    fprintf(stderr, "huh\n");
    execve(argv[1], argvChild, NULL);
}

int main(int argc, char *argv[]) 
{
    // Declare vars
    int childStatus;
    pid_t cpid;

    cpid = fork();
    if (cpid == -1) { // Err check
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    if (cpid == 0) { // In child proc.
        if(argc > 1)
            childsPlay(argc, argv);
        else
            printf("No additional arguments supplied.\n");
    } 
    else { // cpid > 0, in parent proc.
        fprintf(stderr, "CPID: %d\n", cpid);
        waitpid(cpid, &childStatus, 0); // Wait for child to finish
        fprintf(stderr, "Child status: %d\n", childStatus);
    }
    return 0;
}