Log (When Prof. Benson allowed fopen):
I implemented readFile() thinking that two passes through the file was necessary for this assignment. After some reconsideration, I realized that I could process the data as I was reading the file, so I rewrote readFile() to reflect that change.
Processing the data for output was quite simple, as I just used a char array of size eight that held all  '0' 's and replaced values as they were read. From there, it was a simple loop through the array to print the original value read, then binary to decimal conversion and a quick cast to a char.
There was an edge case with fopen() and read() when the last '0' or '1' read was also the end of the file. I added this case in readFile() and added a few helper methods: binaryToDecimal() and getParity().
Manual input on the command line began to give me issues, as I was not sure how to utilize read() with input from the cmd. I stored the input in a large char array and parsed the input similarly to how I did in readFile().

Status (Before 12 February, 2020):
Can read and process any amount of binary numbers given from a .txt file.
Can only process up to 200 chars from manual input. I decided this number was enough for testing, but this number can be increased/decreased through the global inputSize variable.
Tested program through reading all unextended ASCII values from a text file and typing gibberish with some binary values thrown in there for manual input.

Log (no more fopen):
The program will attempt to read a file, if successful, will print the output, if any. If it is unable to find a file, the program will then try to search the cmd
args for any input that might have been given. 
readFile() utilizes read() and open().
inputData() marches along argv[][] for strings to read and process.

Status (After 12 February, 2020):
Will read and process inputs like the following:
	lab_0 file.txt
	lab_0 - 11110000 00001111
	lab_0 11110000 00001111
Otherwise, the program will notify the user that invalid input was received and end the program.