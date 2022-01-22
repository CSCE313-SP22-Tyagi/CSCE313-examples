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
	printf("test1 run with %d cmdline arguments\n", argc);

	//thanks to the above typedef, these mean the same thing
	unsigned long long x1 = 1234;
	Jimmy x2 = 1234;

	char* string = "hello";

	//do some other fun stuff

	if(argc == 1) {
		printf("\nbye\n");
	} else {
		int mode = atoi(argv[1]);
		if(mode == 1) {

			//buffer copying

			Jimmy sz = 1LLU << 24; //16 MB
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
			auto dist = (int*)(&p) - p;
			//
			int a = x + z;
			int b = y + z;
			int c = a + b;
			//
			printf("y (%lu) is at %p; &y (%lu) is at %p (+%ld); *p = %d\n", sizeof(y), (void*)p, sizeof(p), (void*)&p, dist, *p);
			//
			int lower = int(Jimmy(p)) & 0xFFFFFFFF;
			int upper = (Jimmy(p) >> 32) & 0xFFFFFFFF;
			printf("upper = %d, lower = %d\n", lower, upper);

			for(int i = 0; i < 4; i++) {
				printf("*(p+%d) = %d\n", i, *(p+i));
			}
		} else {
			printf("\nmode = 1 or 2\n");
		}
	}

}