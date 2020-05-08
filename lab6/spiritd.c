/* Kyle Chan
    comp 322 - Prof. Benson
    Lab 6: Whack a Mole - spiritd
    8 May, 2020 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

char* moleDirectory;
pid_t cpid1;

typedef void (*sighandler_t)(int);
void sig_handler(int signum) 
{
	if (signum == SIGTERM){
        if (cpid1 == 0)
		    kill(cpid1, SIGKILL);
		exit(EXIT_SUCCESS);
	}

	if (signum == SIGUSR1 || signum == SIGUSR2){
		pid_t mole;
        char *moleNumber;
        int random;
        char *args[4];
		
		switch (mole = fork()) { // fork
            case -1: // ERROR child
                perror("fork");
                exit(EXIT_FAILURE);
            default: // Parent
                cpid1 = mole;
                break;
            case 0: // Child
			    random = rand() % 2;
                moleNumber = random == 1 ? "mole1" : "mole2";
			    args[0] = strcat(moleDirectory, "/moles");
			    args[1] = moleNumber;
                args[2] = moleDirectory;
			    args[3] = '\0';
			    execve(args[0], args, NULL);
		}
	}
}

int main(void)
{
    int i;
    struct rlimit rl;
    // Saves the absolute directory of moles
	char buffer[4096];
	moleDirectory = getcwd(buffer, 4096);
    //printf("%s\n", moleDirectory);
    umask(0); // Clear file creation mask

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        exit(EXIT_FAILURE);
    switch (cpid1 = fork()) { // fork
        case -1: // ERROR child
            exit(EXIT_FAILURE);
        default: // Parent
            exit(0); // Parent exits after fork()
        case 0:
            setsid(); // Create new session
            chdir("/"); // Change cwd
            // Close all open file descriptors
            if (rl.rlim_max == RLIM_INFINITY)
            rl.rlim_max = 1024;
            for (i = 0; (unsigned) i < rl.rlim_max; i++)
                close(i);

            open("/dev/null", O_RDWR);
            dup(0);
            dup(0);

	        signal(SIGUSR1, sig_handler);
	        signal(SIGUSR2, sig_handler);
            signal(SIGTERM, sig_handler);
    }
    while (1) {
		pause();
	}
}