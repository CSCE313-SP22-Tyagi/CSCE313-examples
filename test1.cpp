#include <cstring>
#include <cstdio>

typedef unsigned long long Jimmy;

int main (int argc, char** argv) {
	printf("test1 run with %d cmdline arguments\n", argc);

	//thanks to the above typedef, these mean the same thing
	unsigned long long x1 = 1;
	Jimmy x2 = 1;

	//
	int x = 1111;
	int y = 2222;
	int z = 3333;
	//
	int* p = &y;
	//
	printf("y is at %p; *p = %d, *(p-1) = %d\n", p, *p, *(p-1));

	for(int i = -5; i <= 5; i++) {
		printf("*(p+%d) = %d\n", i, *(p+i));
	}
}