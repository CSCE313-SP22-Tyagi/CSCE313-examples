#include <cstring>
#include <cstdio>
#include <cstdlib>

typedef unsigned long uint64;

int main (int argc, char** argv) {
			
	//
	int x = 1111;
	int y = 2222;
	int z = 3333;
	//
	int* p = &y;
	auto dist = (int*)(&p) - p;
	//
	int a = x + z;
	int b = y + z;
	int c = a + b;
	//
	printf("y (%lu) is at %p; &y (%lu) is at %p (+%ld); *p = %d\n", sizeof(y), (void*)p, sizeof(p), (void*)&p, dist, *p);
	//
	int lower = int(uint64(p)) & 0xFFFFFFFF;
	int upper = (uint64(p) >> 32) & 0xFFFFFFFF;
	printf("upper = %d, lower = %d\n", lower, upper);

	for(int i = 0; i < 4; i++) {
		printf("*(p+%d) = %d\n", i, *(p+i));
	}
}