#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;

typedef unsigned long long Jimmy;

struct test {
	int x;
	int y;
};

class test2 {
	int x; //this is private

	public:

	int y; //this is public

	//this is public
	test2(int val) : x(val), y(val + 1) {}

	//this is public
	int getX() {
		return x;
	}

	private:

	//this is private
	int setX(int x) {
		this->x = x;
	}
};

void func() {

	test t;
	t.x;
	test* tpointer = &t;
	(*tpointer).x;
	tpointer->x;
}

int main (int argc, char** argv) {
	printf("test run with %d cmdline arguments\n", argc);

	//thanks to the above typedef, these mean the same thing
	unsigned long long x1 = 1234;
	Jimmy x2 = 1234;

	char* string = "hello";
}