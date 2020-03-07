/* Kyle Chan
    Lab 2: Launch-Tube, launch.c
    Prof. Benson
    17 March, 2020 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void childsPlay(int argc, char *argv[], char *envp[]) 
{
    // Prepare new argv
    char *argvChild[argc-2];

    // Load all args, except for the first two, into the new array
    for (i = 2; i < argc; i++) {
        argvChild[i] = argv[i];
    }
    // Child executes with supplied commands
    execve(argv[1], argvChild, environ);
}

int main(int argc, char *argv[], char *envp[]) 
{
    // Declare vars
    int childStatus, cpid, i;

    cpid = fork();
    if (cpid > 0) {
        printf("CPID: %d", cpid);
        waitpid(cpid, &childStatus, 0); // Wait for child to finish
        printf("Child status: %d", childStatus);

    } else if (cpid == 0) {
        childsPlay(argc, argv, envp);
    } else {
        // err
    }
    return 0;
}
