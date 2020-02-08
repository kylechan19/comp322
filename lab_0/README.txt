<<<<<<< HEAD
I began my project by outlining basic methods I thought were necessary to complete the project. Those methods were:
	main()
	readFile()
	convertValue()
	inputData()
I implemented readFile() thinking that two passes through the file was necessary for this assignment. After some reconsideration, I realized that I could process the data as I was reading the file, so I rewrote readFile() to reflect that change.
Processing the data for output was quite simple, as I just used a char array of size eight that held all  '0' 's and replaced values as they were read. From there, it was a simple loop through the array to print the original value read, then binary to decimal conversion and a quick cast to a char.
There was an edge case with fopen() and read() when the last '0' or '1' read was also the end of the file. I added this case in readFile() and added a few helper methods: binaryToDecimal() and getParity().
Manual input on the command line began to give me issues, as I was not sure how to utilize read() with input from the cmd. I stored the input in a large char array and parsed the input similarly to how I did in readFile().

Status:
Can read and process any amount of binary numbers given from a .txt file.
Can only process up to 200 chars from manual input. I decided this number was enough for testing, but this number can be increased/decreased through the global inputSize variable.
Tested program through reading all unextended ASCII values from a text file and typing gibberish with some binary values thrown in there for manual input.
=======
I began my project by outlining basic methods I thought were necessary to complete the project. Those methods were:
	main()
	readFile()
	convertValue()
	inputData()
I implemented readFile() thinking that two passes through the file was necessary for this assignment. After some reconsideration, I realized that I could process the data as I was reading the file, so I rewrote readFile() to reflect that change.
Processing the data for output was quite simple, as I just used a char array of size eight that held all  '0' 's and replaced values as they were read. From there, it was a simple loop through the array to print the original value read, then binary to decimal conversion and a quick cast to a char.
There was an edge case with fopen() and read() when the last '0' or '1' read was also the end of the file. I added this case in readFile() and added a few helper methods: binaryToDecimal() and getParity().
Manual input on the command line began to give me issues, as I was not sure how to utilize read() with input from the cmd. I stored the input in a large char array and parsed the input similarly to how I did in readFile().

Status:
Can read and process any amount of binary numbers given from a .txt file.
Can only process up to 200 chars from manual input. I decided this number was enough for testing, but this number can be increased/decreased through the global inputSize variable.
Tested program through reading all unextended ASCII values from a text file and typing gibberish with some binary values thrown in there for manual input.
>>>>>>> 2e497a3e7d024228aa964e8650247838d4426ceb
