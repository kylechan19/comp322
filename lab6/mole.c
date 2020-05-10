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
    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    FILE *logfile = fopen(argv[2], "a+");
	fprintf(logfile, "Pop %s\n", argv[1]);
    fclose(logfile); 
}