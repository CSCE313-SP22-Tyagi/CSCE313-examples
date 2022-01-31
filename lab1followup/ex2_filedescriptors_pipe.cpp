//This program demonstrates the way that file descriptors are inherited by child processes using fork()

#include <cstdio>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>

#include <string>
using std::string;

#define SZ 10

void pipe_read(int fd, string& msg) {
	char buf[SZ];
	memset(buf, 0, SZ);
	//
	read(fd, buf, SZ);
	msg = buf;
}

void pipe_write(int fd, const string& msg) {
	char buf[SZ];
	memset(buf, 0, SZ);
	//
	strcpy(buf, msg.c_str());
	write(fd, buf, SZ);
	printf("sent: \"%s\"\n", buf);
}

int main () {
	//open a pipe
	int fds[2];
	pipe(fds);
	//
	string msg;
	//
	if(fork()) {
		//parent: send 2 messages
		msg = "message 1";
		pipe_write(fds[1], msg);
		msg = "message 2";
		pipe_write(fds[1], msg);
	} else {
		if(fork()) {
			//child 1: recv one message
			pipe_read(fds[0], msg);
			printf("child 1 received: \"%s\"\n", msg.c_str());
		} else {
			//child 2 recv one message
			pipe_read(fds[0], msg);
			printf("child 2 received: \"%s\"\n", msg.c_str());
		}
	}
}