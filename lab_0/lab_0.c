/*  Kyle Chan
    comp 322 Wed
    Lab 0: Making Sense of Ones and Zeros 
    8 Feburary, 2020 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// declare global vars
char *eightBytes;

void readFile(char *filename){
    int inLength, filedes, 
        readingBinNum;

    // Init. file stuff.
    FILE* fp = NULL;
    fp = fopen(*filename, "r");

    /* Process
        Read the entire file one character at a time.
        Store each char into an array that holds a maximum of eight chars, 
            pad with zeroes if necessary.
        Print the eight chars for "Original" output.
        Convert the eight chars -> ascii values.
        Turn the ascii values into either 1 or 0 through subtraction.
        Binary number conversion to decimal. (Ignoring the first bit.)
        Print ascii char for "ASCII" output.
        Print decimal number for "Decimal" output.
        Print parity
        Repeat until EOF. */

    // Checks if the file was found.
    if(fp == NULL)
    {
        // Filename was not found, close the file
        printf("File not found. Please manually input data.");

        // Switch to manual input 
        inputData();
    }

    else
    {
        // Init. array
        eightBytes = (char *)malloc(8 * sizeof(char));

        // Obtain file descriptor
        filedes = fileno(fp);

        /* Buffer the read char to filter possible spaces and 
            newlines at the beginning of data */
        char c;
        read(filedes, &c, 1);

        /* Init. boolean value for read loop. 
            readingBinNum is the toggle to switch between 
            reading '0' or '1', and ' ' or '\n' */
        readingBinNum = (c == ' ' || c == '\n') ? 0 : 1;

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

                /* If the next char is a '0' or '1', 
                    put it in eightBytes[] to be processed later. 
                    Otherwise, stop reading characters and process 
                    what is currently in eightBytes[] */
                if(c == '0' || c == '1')
                {
                    eightBytes[inPos] = c;
                }

                else
                {
                    readingBinNum = 0;
                    inPos = 0;
                    /* ???
                        processData();
                        */
                }
                
            }
            
        }
        
    } 
    // Close the file
    fclose(fp);
}

void inputData(){

}

void processData(){

}

void reInitArr(){
    /* Method description:
        Re-initializes eightBytes[] to all '0'.
        Used for handling multiple series of 1's and 0's
            since only one series of eight characters
            is processed at any given time. */
    int i;
    for(i = 0; i < 8; i++)
    {
        eightBytes[i] = '0';
    }
}

void binaryToDecimal(){

}

void output(){

}

int main(int argc, char *argv[]){

    output();
    // Determine if manual input should happen 
    /*
    if(argc < 2 || argv[2] == "-.txt")
    {
        inputData();
    }

    else
    {
        readFile(argv[2]);
    }
    
    
    */
    return 0;
}