//This program demonstrates the way that file descriptors are inherited by child processes using fork()

#include <cstdio>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string>
using namespace std;

#include <cassert>

#define SZ 100

struct msg {
	int off = 0;
	int len = 0;
};

void parent(int srfd, int swfd) {
	char data[SZ];
	for(int i = 0; i < SZ; i++) {
		data[i] = (i + 1);
	}
	//
	char dummydata[80];
	strcpy(dummydata, "lorem ipsum something idk what else goes here i just need a really long string");
	//
	msg m;
	while(true) {
		read(srfd, &m, sizeof(m));
		if(!m.len) break;
		//
		printf("parent serving %d,%d\n", m.off, m.len);
		//if you uncomment this, it'll behave like the PA1 server, and it will crash :)
		//assert(m.off + m.len <= SZ);
		write(swfd, data + m.off, m.len);
	}
	printf("server done\n");
}

int main () {
	//open a pipe
	int fds1[2];
	pipe(fds1);
	int fds2[2];
	pipe(fds2);
	//server (s) and client (c) read (r) and write (w) handles
	int srfd = fds1[0];
	int swfd = fds2[1];
	int crfd = fds2[0];
	int cwfd = fds1[1];
	//
	if(fork()) {
		char dummydata[80];
		strcpy(dummydata, "hi, this is a really long string that should show up somewhere on the stack");
		//parent: host a data buffer and send chunks in a loop until len = 0
		parent(srfd, swfd);
	} else {
		//child: continually read from prompt and request data
		msg m;
		while(true) {
			cout << "Enter offset and len: ";
			cin >> m.off >> m.len;
			//write the req even if it's the last one, so server knows to exit
			write(cwfd, &m, sizeof(m));
			//
			if(!m.len) break;
			//
			char buf[m.len + 1]; //btw this isn't legal C++, but gcc allows it
			read(crfd, buf, m.len);
			printf("client received: [\033[1;31m");
			for(int i = 0; i < m.len; i++) {
				printf("%d ", buf[i]);
			}
			printf("\033[0m\b]\n");
			//let's print it out as a string and see what we get...
			for(int i = 0; i < m.len; i++) {
				if(!isalnum(buf[i])) buf[i] = ' ';
			}
			buf[m.len] = 0;
			printf("  as string: \"\033[1;32m%s\033[0m\"\n", buf);
		}
		printf("client done\n");
	}

	return 0;
}