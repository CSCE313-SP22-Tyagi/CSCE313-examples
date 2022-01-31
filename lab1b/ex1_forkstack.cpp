#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/types.h>
#include <unistd.h>

#include <string>
using std::string;

int main () {

	constexpr int sz = 32;
	constexpr int sz2 = sz << 20;

	//
	char* tmp = new char[sz2];
	for(int i = 0; i < sz2; i++) {
		tmp[i] = i;
	}
	delete[] tmp;
	//

	char* buf1 = new char[sz];
	strcpy(buf1, "buf1");
	buf1[sz - 1] = 0; //null-terminate

	auto pid = fork();
	string msg = pid ? "parent" : "child";

	char* buf2 = new char[sz];
	buf2[sz - 1] = 0;

	//

	printf("%s 1: %s\n", msg.c_str(), buf1);
	printf("%s 2: %s\n", msg.c_str(), buf2);

	if(pid) {
		//parent
		char* buf3 = new char[sz];
		buf3[sz - 1] = 0;
		printf("%s 3: %s\n", msg.c_str(), buf3);
	} else {
		//child
		char* buf3 = new char[sz];
		buf3[sz - 1] = 0;
		printf("%s 3: %s\n", msg.c_str(), buf3);
	}
}