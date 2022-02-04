//This program demonstrates a lack of proper input sanitization.
//The superficial purpose is to allow the user to search for a specific pattern in a specific file;
//In this case, it runs a loop that takes cmdline input and uses the shell commands --
//  "cat" which in this case just reads the file and outputs its contents
//  "grep" which takes the output from cat and looks line-by-line, printing out the lines that match the user's patterns.
//Example usage: run the program and type "dog" into the prompt to see all lines that contain the substring "dog"
//Example other usage: simply type a single period, ".", into the prompt and grep will print out each line of the file.
//The program also puts quotes around the command, allowing the user to put in words with spaces, like "dog cat".
//The issue comes when a user puts their own quotes into their input: this will allow them to then issue any command they'd like, with full shell access.
//While that may not be an issue in this case, since you ran this program from the cmdline,
//It could be an issue if a function like this existed e.g. on a web server.
//For some possible "exploits" (which won't actually hurt your system), try the following commands (exactly as they appear, including trailing quotes):
//    ." | echo "hacked lol" "
//    ." | echo waiting & echo $(sleep 1 | echo done) "
//    ." | make "clean
//As you can see, the user has full access to our system, and can run any shell commands they'd like to. Very dangerous!
//Whenever you run a program where the user isn't "trusted" -- e.g., a random person on the internet -- you have to be very careful with how you handle their inputs.

#include <cstdio>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string>
using namespace std;

int main () {
	string line;
	while(true) {
		//read user input
		cout << "Enter a search pattern: ";
		getline(cin, line);
		//if line was blank, quit
		if(!line.size()) break;
		//echo user input
		//the weird codes like \033[1;32m change the color on the console, for (hopefully) easier reading :)
		cout << "Arg: \033[1;32m" << line << "\033[0m" << endl;
		//construct entire cmd and print (so we can see what exactly is happening)
		string cmd = "cat test100.txt | grep \"" + line + "\"";
		cout << "Cmd: \033[1;32m" << cmd << "\033[0m" << endl;
		//run the command
		cout << "=================================" << endl;
		system(cmd.c_str());
		cout << "=================================" << endl;
	}
	cout << "Exiting" << endl;

	return 0;
}