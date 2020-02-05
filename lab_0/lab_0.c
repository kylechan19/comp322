/*  Kyle Chan
    comp 322 Wed
    Lab 0: Making Sense of Ones and Zeros 
    8 Feburary, 2020 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int* binaryNums[];

void readFile(char *filename){
    int i, arrLength;
    arrLength = 0;
    FILE* fp = NULL;
    fp = fopen(*filename, "r");

    /* This method will read the file twice. 
        The first pass is to determine the size of the input for array allocation
        The second pass will record the file data into the array */

    /* Checks if the file was found. */
    if(fp == NULL)
    {
        /* Filename was not found, closes the file pointer */
        printf("File not found. Please manually input data.");
        fclose(fp);

        /* Switch to manual input */
        inputData();
    }
    else
    {
        /* Obtain a character count for array allocation. */
        while(feof(fp))
        {
            /* Ignore spaces and \n */
            if(fgetc(fp) != ' ' || fgetc != '\n')
            {
                arrLength++;
            }
        }

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