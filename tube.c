/* Kyle Chan
    Lab 2: Launch-Tube, tube.c
    Prof. Benson
    17 March, 2020 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void childsPlay(int argc, char *argv[], char *envp[]) {

}

int main(int argc, char *argv[], char *envp[]) 
{
    // Declare vars
    int childStatus, cpid;

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