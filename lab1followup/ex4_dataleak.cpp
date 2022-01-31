//This program demonstrates sensitive data leakage
//Depending on the order in which the children run, it's possible for child 1's password to be sent to child 2!

#include <cstdio>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>

#include <string>
using std::string;
using std::to_string;

#define SZ 60

void pipe_read(int fd, string& msg) {
	char buf[SZ];
	memset(buf, 0, SZ);
	//
	read(fd, buf, SZ);
	//do some pre-processing so that middle zeros don't stop printing
	for(int i = 0; i < SZ; i++) {
		if(buf[i] == 0) buf[i] = '_';
	}
	buf[SZ-1] = 0;
	//
	msg = buf;
}

void pipe_write(int fd, const char* label, const string& msg) {
	char buf[SZ];
	memset(buf, 0, SZ);
	//
	strcpy(buf, msg.c_str());
	write(fd, buf, SZ);
	printf("%s sent: \"%s\"\n", label, buf);
	fflush(stdout);
}

void f(int rfd, int wfd) {
	char buf[SZ];
	static int responseNumber = 1;
	if(rfd && wfd) {
		//read message into buf
		read(rfd, buf, SZ);
		printf("server recv \"%s\"\n", buf);
		//copy our response into it
		string msg = "response #" + to_string(responseNumber++);
		strcpy(buf, msg.c_str());
		//do some pre-processing so that middle zeros don't stop printing
		for(int i = 0; i < SZ; i++) {
			if(buf[i] == 0) buf[i] = '_';
		}
		buf[SZ-1] = 0;
		printf("server buf \"%s\"\n", buf);
		//write our response back
		write(wfd, buf, SZ);
	} else {
		memset(buf, 0, SZ);
	}
}

int main () {
	f(0, 0); //init buffer to 0s
	//open two pipes: one for server->client and one for client->server
	int fds1[2];
	pipe(fds1);
	int fds2[2];
	pipe(fds2);
	//
	if(fork()) {
		//parent: send 2 messages
		f(fds2[0], fds1[1]);
		f(fds2[0], fds1[1]);
	} else {
		if(fork()) {
			//child 1: one message
			string msg = "my password is \"\033[1;33mhunter2\033[0m\", don't tell anyone!";
			pipe_write(fds2[1], "child \033[1;34m1\033[0m", msg);
			pipe_read(fds1[0], msg);
			printf("child \033[1;34m1\033[0m received: \"%s\"\n", msg.c_str());
		} else {
			//child 2 one message
			string msg = "hey what's up?";
			pipe_write(fds2[1], "child \033[1;31m2\033[0m", msg);
			pipe_read(fds1[0], msg);
			printf("child \033[1;31m2\033[0m received: \"%s\"\n", msg.c_str());
		}
	}
}