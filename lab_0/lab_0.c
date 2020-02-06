/*  Kyle Chan
    comp 322 Wed
    Lab 0: Making Sense of Ones and Zeros 
    8 Feburary, 2020 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// declare global vars
char eightChars[8];

// There are 33 unprintable ASCII values
//  0-31, and 127
//  each representation has a maximum length of 3
char** unprintables[33][3] = {
    {'N', 'U', 'L'}, {'S', 'O', 'H'}, {'S', 'T', 'X'}, {'E', 'T', 'X'},
    {'E', 'O', 'T'}, {'E', 'N', 'Q'}, {'A', 'C', 'K'}, {'B', 'E', 'L'},
    {'B', 'S', '\0'}, {'T', 'A', 'B'}, {'L', 'F', '\0'}, {'V', 'T', '\0'},
    {'F', 'F', '\0'}, {'C', 'R', '\0'}, {'S', 'O', '\0'}, {'S', 'I', '\0'},
    {'D', 'L', 'E'}, {'D', 'C', '1'}, {'D', 'C', '2'}, {'D', 'C', '3'},
    {'D', 'C', '4'}, {'N', 'A', 'K'}, {'S', 'Y', 'N'}, {'E', 'T', 'B'},
    {'C', 'A', 'N'}, {'E', 'M', '\0'}, {'S', 'U', 'B'}, {'E', 'S', 'C'},
    {'F', 'S', '\0'}, {'G', 'S', '\0'}, {'R', 'S', '\0'}, {'U', 'S', '\0'},
    {'D', 'E', 'L'}
}

void reInitArr(){
    /* Method description:
        Re-initializes values in eightChars[] to all '0'.
        Used for handling consecutive series of 1's and 0's
            since only one series of eight characters
            is processed at any given time. */
    int i;
    for(i = 0; i < 8; i++)
    {
        eightChars[i] = '0';
    }
}

int binaryToDecimal(){
    int i;
    double sum = 0.0;
    
    for(i = 1; i <= 7; i++)
    {
        /* Index starting at eightChars[1] to only process the 7 chars in the 
            unextended ascii format */
        if(eightChars[i] == '1')
            sum += pow((double) 2, (double)(7 - i));
    }
    
    return (int) sum;
}

void inputData(){
    printf("inputDatalul()\n");
}

void readFile(char* filename){
    int inPos, filedes, readingBinNum, binToInt;
    char c;

    // Init. file stuff.
    FILE* fp;
    fp = fopen(filename, "r");

    // Checks if the file was found.
    if(fp == NULL)
    {
        // Filename was not found, close the file
        printf("File not found. Please manually input data.");

        // Close file and switch to manual input 
        fclose(fp);
        inputData();
    }

    else
    {
        // Obtain file descriptor
        filedes = fileno(fp);

        // Buffer the read char to filter possible spaces and 
        //    newlines at the beginning of data 
        read(filedes, &c, 1);

        // Init. boolean value for read loop. 
        //    readingBinNum is the toggle to switch between 
        //    reading '0' or '1', and ' ' or '\n' 
        readingBinNum = (c == ' ' || c == '\n') ? 0 : 1;
        
        // Flush eightChars[] because idk how array values are init. by default.
        reInitArr();

        // Read until EOF
        while(c != -1)
        {
            while(!readingBinNum && c != -1)
            {
                read(filedes, &c, 1);
                readingBinNum = (c == ' ' || c == '\n') ? 0 : 1;
            }

            for(inPos = 0; readingBinNum && inPos < 8; inPos++)
            {
                // Get the next char.
                read(filedes, &c, 1);

                // If the next char is a '0' or '1', 
                //    put it in eightChars[] to be processed later. 
                //    Otherwise, stop reading characters and process 
                //    what is currently in eightChars[] 
                if(c == '0' || c == '1')
                {
                    eightChars[inPos] = c;
                }

                // Process and output data.
                else
                {
                    // Reset local variables.
                    readingBinNum = 0;
                    inPos = 0;

                    // Convert to binary
                    binToInt = binaryToDecimal();

                    // Send converted value to be printed.
                    output(binToInt);

                    // Flush eightChars[].
                    reInitArr();
                }
                
            }
            
        }

        // Close the file
        fclose(fp);
    } 
}

void output(int decimalNum){
    int i;
    char asciiVal;
    char* unprintable;

    // Print original
    for(i = 0; i < 8; i++){
        printf("%c", eightChars[i]);
    }
    // Check if we read an unprintable ASCII val.
    if(decimalNum <= 31 || decimalNum == 127){
        (decimalNum == 127) ? unprintable = unprintables[32] : unprintable = unprintables[decimalNum];
    }
    printf("        ");
    printf("%c", asciiVal)

}

int main(int argc, char** argv){

    // Determine if manual input should happen 
    
    if(argc < 2 || *argv[2] == '-')
    {
        printf("Original ASCII    Decimal  Parity/n
         -------- -------- -------- --------\n");
        inputData();
    }

    else
    {
        printf("Original ASCII    Decimal  Parity/n
         -------- -------- -------- --------\n");
        readFile(argv[2]);
    }
    
    
    return 0;
}