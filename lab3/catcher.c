/* Kyle Chan
    comp 322 - Prof. Benson
    Lab 3: Catcher
    23 March, 2020 */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// declare global vars
static int sigCount = 0;
// SKIP: 9) SIGKILL, 19) SIGSTOP
static int sigs[] = {SIGHUP, SIGINT, SIGQUIT, SIGILL, SIGTRAP, SIGABRT, SIGIOT, SIGBUS, SIGFPE,
    SIGUSR1, SIGSEGV, SIGUSR2, SIGPIPE, SIGALRM, SIGTERM, SIGSTKFLT, SIGCHLD, SIGCONT, 
    SIGTSTP, SIGTTIN, SIGTTOU, SIGURG, SIGXCPU, SIGXFSZ, SIGVTALRM, SIGPROF, SIGWINCH};

// length of sigs/inputs
static const int SIGS_LEN = 27;

static char *inputs[] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "IOT", "BUS", "FPE",
    "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT", "CHLD", "CONT", 
    "TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF", "WINCH"};

typedef void (*sighandler_t)(int);

void sig_handler(int signum) 
{
    signal(signum, sig_handler);
    pause();
}

void printSig(int signum) 
{
    //printf("%s\n", strsignal(sigs[signum]));
    printf("SIG%s caught at %ti\n", inputs[signum], time(NULL));
    sigCount++;
}

void parseCmd(int argc, char *argv[]) 
{
    int i, j, successiveTerm, termCount;
    successiveTerm = 0;

    // Loop through argv
    for (i = 1; i < argc; i++) {
        // Loop through listed signals.
        for (j = 0; j < SIGS_LEN; j++) {
            // Catch IOT or IO and map to ABRT
            if (strcmp(argv[i], "IOT") == 0 || strcmp(argv[i], "IO") == 0) {
                signal(SIGABRT, sig_handler);
                printSig(5);
                break;
            }
            else if (strcmp(argv[i], inputs[j]) == 0) {
                signal(sigs[j], sig_handler);
                printSig(j);
                break;
            }
        }
        // Toggle to detect successive TERM
        successiveTerm = (j == 14) ? 1 : 0;

        if (successiveTerm) {
            termCount++;
        } 
        else {
            termCount = 0;
        }
        // Received three successive TERM
        if (termCount == 3) {
            break;
        }
    }
}

int main(int argc, char *argv[]) 
{   
    // Declare vars
    int pid;
    if (argc < 2)
        printf("Too few arguments.\n");
    else {
        pid = getpid(),
        fprintf(stderr, "catcher: $$ = %d\n", pid);
        parseCmd(argc, argv);
        fprintf(stderr, "catcher: Total signals count = %d\n", sigCount);
    }
    fprintf(stderr, "End of lab3-catcher.\n");
    return 0;
}