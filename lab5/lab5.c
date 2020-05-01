/* Kyle Chan
    comp 322 - Prof. Benson
    Lab 5: Page/Offset Calculation
    8 May, 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static int pageSize = 4096;

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("Not enough arguments\n");
        return -1;
    }
    unsigned int address = atoi(argv[1]); // Convert given addres to an int through atoi()
    unsigned int pageNumber = address / pageSize; // Calculate page number
    unsigned int offset = address % pageSize; // Calculate offset
    printf("The address %d contains: \npage number = %d \noffset = %d\n", address, pageNumber, offset);
    return 1;
}