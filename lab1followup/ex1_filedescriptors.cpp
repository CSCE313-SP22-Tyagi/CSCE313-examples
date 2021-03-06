//This program demonstrates the way that file descriptors are inherited by child processes using fork()

#include <cstdio>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>

int main () {
	const char* file = "test10.txt"; //file path
	constexpr int sz = 10; //file size: 100 bytes
	char buf[sz + 1]; //buffer to hold file contents
	memset(buf, 0, sz + 1);
	//
	int fd = open(file, O_RDONLY);
	//step 1: read and print all file contents in single process
	read(fd, buf, sz);
	printf("FILE CONTENTS (A): \"%s\"\n", buf);
	//reset buffer and seek back to the front
	memset(buf, 0, sz + 1);
	lseek(fd, 0, SEEK_SET);
	//split process and do it again
	if(fork()) {
		//parent
		printf("parent file descriptor: %d\n", fd);
		printf("parent file location: %ld\n", lseek(fd, 0, SEEK_CUR));
		if(read(fd, buf, sz) < 0) {
			perror("parent");
		}
		printf("FILE CONTENTS (parent): \"%s\"\n", buf);
	} else {
		//child
		printf("child file descriptor: %d\n", fd);
		printf("child file location: %ld\n", lseek(fd, 0, SEEK_CUR));
		if(read(fd, buf, sz) < 0) {
			perror("child");
		}
		printf("FILE CONTENTS (child): \"%s\"\n", buf);
	}
	//of the parent and child, whichever goes first will print the content of the file
	//the second will see that its own file pointer has moved to the EOF, and will not receive any data
	//this is because their file descriptors point to the same entry in the OS open file table,
	//so the file pointer is the same for both processes
}