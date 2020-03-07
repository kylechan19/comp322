/* Kyle Chan
    Lab 2: Launch-Tube, launch.c
    Prof. Benson
    14 March, 2020 */

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
    char* args[argc-1];

    int j = 0;
    for (i = 1; i < argc-1; i++) {
        args[j] = argv[i]; // Put args for child process
        j++;
    }
    // Child executes with supplied commands
    execve(argv[1], args, NULL);
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