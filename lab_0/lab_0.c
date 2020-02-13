/*  Kyle Chan
    comp 322 Wed
    Lab 0: Making Sense of Ones and Zeros 
    8 Feburary, 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

// declare global vars
char eightChars[8];

// There are 34 unprintable ASCII values
//  0-31, 'space', and 127
char *unprintables[] = {
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
    " BS", "TAB", " LF", " VT", " FF", " CR", " SO", " SI",
    "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",
    "CAN", " EM", "SUB", "ESC", " FS", " GS", " RS", " US",
    "space", "DEL"};

void CRASHER(){
    // Gracefully exit prog.
    printf("Invalid input.\n");
    printf("End of lab_0.");
    exit(0);
}

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
    int i, j, parity, numSpaces;
    char asciiVal;

    // Print original
    for (i = 0; i < 8; i++)
    {
        printf("%c", eightChars[i]);
    }

    // Check if we read an unprintable ASCII val.
    if (decimalNum <= 31)
    {   
        printf("      %s", unprintables[decimalNum]);
    }
    // space char.
    else if(decimalNum == 32)
    {
        printf("    %s", unprintables[decimalNum]);
    }
    else if(decimalNum == 127)
    {
        printf("      %s", unprintables[33]);
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

void inputData(int argc, char **argv){
    int argPt, inPos, binToInt, arrIndex;
    char c;
    inPos = 0;
    arrIndex = 0;
    argPt = (*argv[1] == '-') ? 2 : 1;

    printf("Original ASCII    Decimal  Parity\n-------- -------- -------- --------\n");
    // Read strings until we come upon end of cmd input or invalid input.
    while(argPt < argc)
    {
        // Read characters until end of string or invalid input
        while(argv[argPt][arrIndex] != '\0'){

            c = argv[argPt][arrIndex];
            if(c == '1' || c == '0')
            {
                if(inPos < 8)
                {
                    // Insert c into the next position in eightBytes[].
                    eightChars[inPos++] = c;
                }

                // eightChars is full, begin proccessing
                if (inPos == 8)
                {
                    // Send converted value to be printed.
                    binToInt = binaryToDecimal();
                    output(binToInt);

                    // Flush eightChars[] and get next binary value, if possible.
                    reInitArr();
                    inPos = 0;
                }
            }
            // Invalid input
            else
            {
                CRASHER();
            }

            // Move to next char in string
            arrIndex++;
        }
        
        // End of string
        // This is where padding of zeroes on the right would happen
        if(inPos > 0)
        {
            // Send converted value to be printed.
            binToInt = binaryToDecimal();
            output(binToInt);

            // Flush eightChars[] and get next binary value.
            reInitArr();
            inPos = 0;
        }

        // Move to next val in argv
        argPt++;
        arrIndex = 0;
    }
}

int readFile(char *filename){
    int filedes, bytesRead, inPos, binToInt;
    char c = ' ';
    inPos = 0;

    // Init. eightChars[] because idk how array values are init. by default.
    reInitArr();

    // Get file descriptor.
    filedes = open(filename, O_RDONLY);

    // file not found
    if(filedes == -1){
        printf("No file found. Checking argv for input...\n");
        return 0;
    }

    printf("Original ASCII    Decimal  Parity\n-------- -------- -------- --------\n");
    // Read characters until we come upon end of file or invalid input.
    while(read(filedes, &bytesRead, 1) > 0)
    {
        c = (char)bytesRead;
        if(c == '1' || c == '0')
        {
            if(inPos < 8)
            {
                // Insert c into the next position in eightBytes[].
                eightChars[inPos++] = c;
            }

            // eightChars is full, begin proccessing
            if (inPos == 8)
            {
                // Send converted value to be printed.
                binToInt = binaryToDecimal();
                output(binToInt);

                // Flush eightChars[] and get next binary value, if possible.
                reInitArr();
                inPos = 0;
            }
        }

        else if(c == ' ' || c == '\n')
        {
            // This is where padding of zeroes on the right would happen
            if(inPos > 0)
            {
                // Send converted value to be printed.
                binToInt = binaryToDecimal();
                output(binToInt);

                // Flush eightChars[] and get next binary value.
                reInitArr();
                inPos = 0;
            }
        }

        // Invalid input
        else // It's the case that (c != '0' || c != '1' || c != ' ' || c != '\n')
        {
            CRASHER();
        }
    }

    // Edge case where the last readable char is the last byte in the file
    if (inPos > 0)
    {
        // Send converted value to be printed.
        binToInt = binaryToDecimal();
        output(binToInt);
    }
    // Close the file
    close(filedes);
    return 1;
}

int main(int argc, char **argv){
    int readFileSuccess;
    // check for no args
    if (argc < 2)
    {
        // exit prog.
        CRASHER();
    }

    // Check if input received from cmd
    else if(*argv[1] == '-' || *argv[1] != '\0')
    {
        // Try reading a file first.
        readFileSuccess = readFile(argv[1]);

        // If successful, end prog., otherwise, attempt to read cmd line for input.
        readFileSuccess == 1 ? printf("End of lab_0") : inputData(argc, argv);
    }
    else
    {
        // exit prog.
        CRASHER();
    }

    return 0;
}
