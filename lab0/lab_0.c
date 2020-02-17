/*  Kyle Chan
    comp 322 Wed
    Lab 0: Making Sense of Ones and Zeros 
    15 Feburary, 2020 */

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

void reInitArr() 
{
    // Re-initializes values in eightChars[] to all '0'.
    int i;
    for (i = 0; i < 8; i++) {
        eightChars[i] = '0';
    }
}

int binaryToDecimal() 
{
    int i;
    double sum = 0.0;

    for (i = 1; i <= 7; i++) {
        /* Index starting at eightChars[1] to only process the 7 chars from left to right
            in the unextended ascii format. This is where the math.h library is used for
            the sake of readability. */
        if (eightChars[i] == '1')
            sum += pow(2.0, (double)(7 - i));
    }
    return (int)sum;
}

int getParity() 
{
    // Determines if an even or odd amount of 1's were read.
    int parity, i;
    for (i = 0; i < 8; i++) {
        if (eightChars[i] == '1')
            parity++;
    }
    return parity % 2;
}

void output(int decimalNum) 
{
    int i, j, parity, numSpaces;

    // Print original characters read.
    for (i = 0; i < 8; i++) {
        printf("%c", eightChars[i]);
    }

    // Check for unprintable ASCII values.
    if (decimalNum <= 31) {   
        printf("      %s", unprintables[decimalNum]);
    }
    else if (decimalNum == 32) {
        // space char.
        printf("    %s", unprintables[decimalNum]);
    }
    else if (decimalNum == 127) {
        // DEL
        printf("      %s", unprintables[33]);
    }
    else {
        // Print the printable ASCII val.
        printf("        %c", (char)decimalNum);
    }

    /* Print decimal value. These checks are for formatting the 
        decimal value with the correct amount of spaces. */

    // Only one digit to print.
    if (decimalNum < 10)
        numSpaces = 8;

    // Two digits.
    else if (decimalNum < 100)
        numSpaces = 7;

    // A WHOPPING THREE DIGITS.
    else
        numSpaces = 6;

    // Prin the spaces.
    for (j = 0; j < numSpaces; j++) {
        printf(" ");
    }
    printf("%d ", decimalNum);

    // Print parity
    parity = getParity();
    (parity == 0) ? printf("EVEN\n") : printf("ODD\n");
}

void inputData(int argc, char **argv) 
{
    int argPt, inPos, binToInt, arrIndex, receivedInvalidInput;
    char c;
    inPos = 0;
    arrIndex = 0;
    receivedInvalidInput = 0;

    // Check if '-' was entered in cmd or not
    argPt = (*argv[1] == '-') ? 2 : 1;

    printf("Original ASCII    Decimal  Parity\n-------- -------- -------- --------\n");
    // Read strings until we come upon end of cmd input or invalid input.
    while (argPt < argc) {
        // Read characters until end of string or invalid input.
        while (argv[argPt][arrIndex] != '\0') {

            // Retrieve the character from argv then check if it is valid input.
            c = argv[argPt][arrIndex];
            if (c == '1' || c == '0') {

                // It's the case that eightChars[] is NOT full.
                if (inPos < 8) {
                    // Insert c into the next position in eightChars[].
                    eightChars[inPos++] = c;
                }

                // eightChars is full, begin proccessing
                if (inPos == 8) {
                    // Send converted value to be printed.
                    binToInt = binaryToDecimal();
                    output(binToInt);

                    // Flush eightChars[] and get next binary value, if possible.
                    reInitArr();
                    inPos = 0;
                }
            }

            // Invalid input
            else {
                printf("Invalid input.\n");
                receivedInvalidInput = 1;
                break;
            }

            // Move to next char in string
            arrIndex++;
        }
        
        // End of string
        // This is where padding of zeroes on the right would happen.
        if (inPos > 0 && !receivedInvalidInput) {
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

int readFile(char *filename)
{
    int filedes, bytesRead, inPos, binToInt, receivedInvalidInput;
    char c = ' ';
    inPos = 0;
    receivedInvalidInput = 0;

    // Init. eightChars[] because idk how array values are init. by default.
    reInitArr();

    // Get file descriptor.
    filedes = open(filename, O_RDONLY);

    // file not found
    if (filedes == -1) {
        printf("No file found.\n");
        return 0;
    }

    printf("Original ASCII    Decimal  Parity\n-------- -------- -------- --------\n");
    // Read characters until we come upon end of file or invalid input.
    while (read(filedes, &bytesRead, 1) > 0) {

        c = (char)bytesRead;
        // Check for valid input.
        if (c == '1' || c == '0') {
            if (inPos < 8) {
                // Insert c into the next position in eightBytes[].
                eightChars[inPos++] = c;
            }

            // eightChars is full, begin proccessing
            if (inPos == 8) {
                // Send converted value to be printed.
                binToInt = binaryToDecimal();
                output(binToInt);

                // Flush eightChars[] and get next binary value, if possible.
                reInitArr();
                inPos = 0;
            }
        }

        else if (c == ' ' || c == '\n') {
            // This is where padding of zeroes on the right would happen
            if(inPos > 0) {
                // Send converted value to be printed.
                binToInt = binaryToDecimal();
                output(binToInt);

                // Flush eightChars[] and get next binary value.
                reInitArr();
                inPos = 0;
            }
        }

        // Invalid input
        else {
            printf("Invalid input.\n");
            receivedInvalidInput = 1;
            break;
        }
    }

    // Edge case where the last readable char is the last byte in the file.
    if (inPos > 0 && !receivedInvalidInput) {
        // Send converted value to be printed.
        binToInt = binaryToDecimal();
        output(binToInt);
    }
    // Close the file
    close(filedes);
    return 1;
}

int main(int argc, char **argv) 
{
    int readFileSuccess;
    // check for no args
    if (argc < 2) {
        // exit prog.
        printf("No args found.\n");
    }

    // Check if input received from cmd, ignores empty input
    else if (*argv[1] == '-' || *argv[1] != '\0') {
        // Try reading a file first.
        readFileSuccess = readFile(argv[1]);

        // If successful, end prog., otherwise, attempt to read cmd line for input.
        readFileSuccess == 1 ? printf("Read from file: %s \n", argv[1]) : inputData(argc, argv);
    }

    else {
        // Invalid input
        printf("Invalid input.\n");
    }

    printf("End of lab_0.");
    return 0;
}
