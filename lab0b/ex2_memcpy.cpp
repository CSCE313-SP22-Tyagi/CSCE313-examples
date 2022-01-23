#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration;

typedef unsigned long uint64;

//why should we use memcpy?
//well, first of all, it makes a lot of code way simpler -
//but perhaps more importantly, it's *way* faster!
int main () {

	//buffer copying

	//"LU" at the end of a number is shorthand to make it an unsigned long
	//this helps ensure we won't accidentally overflow
	//because e.g. (1 << 40) will overflow and become 0,
	//since 1 is an int with 32 bits
	uint64 sz = 1LU << 24; //16 MB; the bigger you make this, the better memcpy will be
	//these lines allocate two byte arrays, each with sz elements
	//in this case, sz = 2^24 = 16777216, or 16 MB of data
	char* src = new char[sz];
	char* dst = new char[sz];

	//let's time two data-copying approaches:
	//first, a byte-by-byte for loop
	//second, memcpy

	//method 1
	auto begin1 = high_resolution_clock::now();
	{
		//manually copy each byte from src to dst
		//up to the limit of sz bytes
		for(uint64 i = 0; i < sz; i++) {
			dst[i] = src[i];
		}
	}
	auto end1 = high_resolution_clock::now();
	double time1 = duration<double, std::milli>(end1 - begin1).count();
	printf("forloop time: %.2f ms\n", time1);

	//now we'll do a nice, simple memcpy :^)

	//method 2
	auto begin2 = high_resolution_clock::now();
	{
		//copy sz bytes from src to dst
		memcpy(dst, src, sz);
	}
	auto end2 = high_resolution_clock::now();
	double time2 = duration<double, std::milli>(end2 - begin2).count();
	printf("memcpy time: %.2f ms\n", time2);

	printf("memcpy is %.1fx faster\n", time1 / time2);

	//if you compile this with address sanitizer,
	//it will throw an error unless you uncomment these two lines
	//since there is currently a memory leak -
	//our two buffers were created on the heap,
	//so now we need to delete them

	//delete[] src;
	//delete[] dst;

	//:D
	return 0;
}