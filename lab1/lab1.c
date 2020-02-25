/* Kyle Chan
    Lab 1: Time and Forking Children
    Prof. Benson
    29 February, 2020 */

#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void reportProcInfo(int childStatus, int cpid)
{
    // Used by both parent and child proccesses to print their own information.

    // Print PID and PPID
    printf("PID: %d PPID: %d ", 
        getpid(),  
        getppid());

    // If applicable, print CPID and the child process' return value.
    if (cpid > 0) {
        printf("CPID: %d RETVAL: %d\n", 
            cpid, 
            childStatus);
            
    } 
    else {
        // format then close child process
        printf("\n");
        _exit(EXIT_SUCCESS);
    }
}

int main() 
{
    // declare vars and times() struct
    int sec, childStatus, cpid;
    struct tms daTimes;

    // Print START time
    sec = time(NULL);
    printf("START %d\n", sec);

    childStatus = fork(); // Create child process and store its status

    cpid = waitpid(childStatus, &childStatus, 0); // Wait for child to finish

    reportProcInfo(childStatus, cpid); // Parent + child report on their information

    times(&daTimes); // Store process times

    // Print process times
    printf("USER: %ld SYS: %ld\nCUSER: %ld CSYS: %ld\n",
        (long)daTimes.tms_utime,
        (long)daTimes.tms_stime,
        (long)daTimes.tms_cutime,
        (long)daTimes.tms_cstime);

    // Print END time
    sec = time(NULL);
    printf("END %d\n", sec);
    return 0;
}
