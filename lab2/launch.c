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
    int i, j;
    char* args[argc-1];

    j = 0;
    for (i = 1; i < argc; i++) {
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
    
    if (argc < 2) {
        printf("Too few arguments.\n");
    }
        else {
        cpid = fork();
        if (cpid == -1) { // Err check
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        if (cpid > 0) { // In parent proc.
            fprintf(stderr, "Launch CPID: %d\n", cpid);
            wait(&childStatus); // Wait for child to finish
            fprintf(stderr, "Launch Child Status: %d\n", childStatus);
        } 
        if (cpid == 0) { // In child proc.
            childsPlay(argc, argv);
        }
    }
    fprintf(stderr, "End of lab2-launch.\n");
    return 0;
}