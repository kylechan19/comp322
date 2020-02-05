/*  Kyle Chan
    comp 322 Wed
    Lab 0: Making Sense of Ones and Zeros 
    8 Feburary, 2020 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void readFile(char *filename){
    int i;
    FILE* fp = NULL;
    fp = fopen(*filename, "r");

    /* Read the entire file eight characters at a time.
        Convert these from char -> int, store each integer into an array, pad with zeroes if necessary
        Print the eight integers for output.
        Binary to integer conversion.
        Output the conversion.
        Output corresponding ascii value, if possible.
        Repeat for until EOF. */

    /* Checks if the file was found. */
    if(fp == NULL)
    {
        /* Filename was not found, close the file */
        printf("File not found. Please manually input data.");
        fclose(fp);

        /* Switch to manual input */
        inputData();
    }
    
    else
    {
        
    }
    
}

void inputData(){

}

void checkEightComplement(){

}

void convertValue(){

}

void output(){

}

int main(int argc, char *argv[]){

    /* Determine if manual input should happen */
    if(argc < 2 || argv[2] == "-.txt")
    {
        inputData();
    }

    /*  */
    else
    {
        readFile(argv[2]);
    }
    
    /* output */

    return 0;
}