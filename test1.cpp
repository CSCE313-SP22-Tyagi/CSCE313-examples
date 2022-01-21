#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;

typedef unsigned long long Jimmy;

int main (int argc, char** argv) {
	printf("test1 run with %d cmdline arguments\n", argc);

	//thanks to the above typedef, these mean the same thing
	unsigned long long x1 = 1234;
	Jimmy x2 = 1234;

	//do some other fun stuff

	if(argc == 1) {
		printf("\nbye\n");
	} else {
		int mode = atoi(argv[1]);
		if(mode == 1) {

			//buffer copying

			Jimmy sz = 1LLU << 24;
			char* src = new char[sz];
			char* dst = new char[sz];

			//method 1
			auto begin1 = high_resolution_clock::now();
			{
				for(Jimmy i = 0; i < sz; i++) {
					dst[i] = src[i];
				}
			}
			auto end1 = high_resolution_clock::now();
			printf("time: %f ms\n", duration<double, std::milli>(end1 - begin1).count());

			//method 2
			auto begin2 = high_resolution_clock::now();
			{
				memcpy(dst, src, sz);
			}
			auto end2 = high_resolution_clock::now();
			printf("time: %f ms\n", duration<double, std::milli>(end2 - begin2).count());

			//delete[] src;
			//delete[] dst;
		}
		else if(mode == 2) {
			
			//
			int x = 1111;
			int y = 2222;
			int z = 3333;
			//
			int* p = &y;
			//
			int a = x + z;
			int b = y + z;
			int c = a + b;
			//
			printf("y (%lu) is at %p; &y (%lu) is at %p; *p = %d\n", sizeof(y), (void*)p, sizeof(p), (void*)&p, *p);

			for(int i = 0; i < 4; i++) {
				printf("*(p+%d) = %d\n", i, *(p+i));
			}
		} else {
			printf("\nmode = 1 or 2\n");
		}
	}

}