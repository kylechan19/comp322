/* Kyle Chan
    comp 322 - Prof. Benson
    Lab 6: Whack a Mole - mole
    8 May, 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *moleDirectory;
    char buffer[4096];
	moleDirectory = getcwd(buffer, 4096);
    printf("%s\n", moleDirectory);
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }
    FILE *logfile = fopen("./lab6.txt", "a+");
	fprintf(logfile, "Pop %s\n", argv[1]);
    fclose(logfile);
}