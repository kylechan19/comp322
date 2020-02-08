/*  Kyle Chan
    comp 322 Wed
    Lab 0: Making Sense of Ones and Zeros 
    8 Feburary, 2020 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include <time.h>

// declare global vars
char eightChars[8];
int inputSize = 200;

// There are 33 unprintable ASCII values
//  0-31, and 127
//  each representation has a maximum length of 3
char *unprintables[] = {
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
    " BS", "TAB", " LF", " VT", " FF", " CR", " SO", " SI",
    "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
    "CAN", " EM", "SUB", "ESC", " FS", " GS", " RS", " US",
    "DEL"};

void reInitArr(){
    // Re-initializes values in eightChars[] to all '0'.
    int i;
    for (i = 0; i < 8; i++)
    {
        eightChars[i] = '0';
    }
}

int binaryToDecimal(){
    int i;
    double sum = 0.0;

    for (i = 1; i <= 7; i++)
    {
        /* Index starting at eightChars[1] to only process the 7 chars in the 
            unextended ascii format */
        if (eightChars[i] == '1')
            sum += pow((double)2, (double)(7 - i));
    }
    return (int)sum;
}

int getParity(){
    int parity, i;
    for (i = 0; i < 8; i++)
    {
        if (eightChars[i] == '1')
            parity++;
    }
    return parity % 2;
}

void output(int decimalNum){
    int i, j, parity, numSpaces, unprintIndex;
    char asciiVal;

    // Print original
    for (i = 0; i < 8; i++)
    {
        printf("%c", eightChars[i]);
    }

    // Check if we read an unprintable ASCII val.
    if (decimalNum <= 31 || decimalNum == 127)
    {
        unprintIndex = (decimalNum == 127) ? 32 : decimalNum;
        printf("      %s", unprintables[unprintIndex]);
    }

    else
    {
        // Print the printable ASCII val.
        asciiVal = (char)decimalNum;
        printf("        %c", asciiVal);
    }

    // Print decimal value.
    // Only one digit to print.
    if (decimalNum < 10)
        numSpaces = 8;

    // Two digits.
    else if (decimalNum < 100)
        numSpaces = 7;

    // A WHOPPING THREE DIGITS.
    else
        numSpaces = 6;

    for (j = 0; j < numSpaces; j++)
    {
        printf(" ");
    }
    printf("%d ", decimalNum);

    // Print parity
    parity = getParity();
    (parity == 0) ? printf("EVEN\n") : printf("ODD\n");
}

void inputData(){
    char input[inputSize];
    int i, binToInt, readingBinNum, inPos;
    i = 0;
    inPos = 0;

    char c = ' ';
    reInitArr();
    printf("Enter data: \n");
    gets(input);
    printf("Original ASCII    Decimal  Parity\n-------- -------- -------- --------\n");

    // Process input.
    while (input[i] != '\0')
    {
        c = input[i++];
        readingBinNum = (c == '0' || c == '1') ? 1 : 0;

        if (readingBinNum && inPos < 8)
        {
            // Insert c into the next position in eightBytes[].
            eightChars[inPos++] = c;
        }

        // Process and output data if we finished reading
        //  enough binary nums or a non '1' or '0' byte was read.
        if (inPos == 8)
        {
            // Convert to binary
            binToInt = binaryToDecimal();

            // Send converted value to be printed.
            output(binToInt);

            // Flush eightChars[] and get next binary value.
            reInitArr();
            inPos = 0;
        }
        // Only the last series of 1's and 0's could possibly have less length less than 8.
        //  break out after outputting result
        else if (inPos > 0 && !readingBinNum)
        {
            // Convert to binary
            binToInt = binaryToDecimal();

            // Send converted value to be printed.
            output(binToInt);

            // Flush eightChars[] and get next binary value.
            reInitArr();
            inPos = 0;
        }
    }

    if (inPos > 0)
    {
        // Convert to binary
        binToInt = binaryToDecimal();

        // Send converted value to be printed.
        output(binToInt);
    }
}

void readFile(char *filename){
    int filedes, bytesRead, readingBinNum, inPos, binToInt;
    char c = ' ';
    inPos = 0;

    // Init. file stuff.
    FILE *fp;
    fp = fopen(filename, "r");

    // Checks if the file was found.
    if (fp == NULL)
    {
        // Filename was not found, close the file
        printf("File not found. Please manually input data:\n");

        // Switch to manual input.
        inputData();
    }

    else
    {
        // Init. eightChars[] because idk how array values are init. by default.
        reInitArr();

        // Obtain file descriptor
        filedes = fileno(fp);

        // Filter data for binary values.
        while (read(filedes, &bytesRead, 1) > 0)
        {
            c = (char)bytesRead;
            readingBinNum = (c == '0' || c == '1') ? 1 : 0;

            if (readingBinNum && inPos < 8)
            {
                // Insert c into the next position in eightBytes[].
                eightChars[inPos++] = c;
            }
            // Process and output data if we finished reading
            //  enough binary nums or a non '1' or '0' byte was read.
            if (inPos == 8)
            {
                // Convert to binary
                binToInt = binaryToDecimal();

                // Send converted value to be printed.
                output(binToInt);

                // Flush eightChars[] and get next binary value.
                reInitArr();
                inPos = 0;
            }
            // Only the last series of 1's and 0's could possibly have less length less than 8.
            //  break out after outputting result
            else if (inPos > 0 && !readingBinNum)
            {
                // Convert to binary
                binToInt = binaryToDecimal();

                // Send converted value to be printed.
                output(binToInt);

                // Flush eightChars[] and get next binary value.
                reInitArr();
                inPos = 0;
            }
        }
    }

    // Edge case where the last readable char is the last byte in the file
    // At this point, bytesRead should be <=0, so it is safe to only check inPos
    if (inPos > 0)
    {
        // Convert to binary
        binToInt = binaryToDecimal();

        // Send converted value to be printed.
        output(binToInt);
    }
    // Close the file
    fclose(fp);
}

int main(int argc, char **argv){

    // Determine if manual input should happen
    if (argc < 2 || *argv[1] == '-')
    {
        inputData();
    }

    else
    {
        printf("Original ASCII    Decimal  Parity\n-------- -------- -------- --------\n");
        readFile(argv[1]);
    }

    return 0;
}