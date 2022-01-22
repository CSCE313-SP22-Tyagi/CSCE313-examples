#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;

typedef unsigned long uint64;

int main (int argc, char** argv) {

	//buffer copying

	uint64 sz = 1LU << 24; //16 MB
	char* src = new char[sz];
	char* dst = new char[sz];

	//method 1
	auto begin1 = high_resolution_clock::now();
	{
		for(uint64 i = 0; i < sz; i++) {
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