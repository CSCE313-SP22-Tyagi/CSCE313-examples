#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string>
using std::string;

void f(const char* str) {
	char buf[100];
	if(str) {
		//do some pre-processing so that middle zeros don't stop printing
		for(int i = 0; i < 99; i++) {
			if(buf[i] == 0) buf[i] = ' ';
		}
		buf[99] = 0;
		//
		printf("current contents of buf: \"%s\"\n", buf);
		strcpy(buf, str);
		printf("new contents of buf: \033[1;32m\"%s\"\033[0m\n", buf);
	} else {
		memset(buf, 0, 100);
	}
}

int main () {
	f(nullptr); //zero-out just in case
	f("test");
	f("test again");
	f("this is a really long string");
	f("this string has a \033[1;31mPASSWORD\033[0m in it");
	f("short string");
	f("what now?");
	f("!");
}