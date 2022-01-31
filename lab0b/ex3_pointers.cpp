//This program demonstrates a bit of pointer logic and stack manipulation

#include <cstring>
#include <cstdio>
#include <cstdlib>

typedef unsigned long uint64;

//BYOB: bring your own basicfunctionimplementations
long min(long i, long j) {
	return i < j ? i : j;
}
long max(long i, long j) {
	return i > j ? i : j;
}

//pointers can be a bit complicated at first,
//but practice will make them much more intuitive
int main () {
	//first, we'll just define some integers on the stack
	int x = 1111;
	int z = 2222;
	int y = x + z;
	//p is a pointer, which is on the stack since it's a local variable,
	//pointing to y, which is also on the stack
	//so *don't* use delete on it! only delete stuff on the heap!
	int* p = &y;
	//this tells us "how many integers away" p is from y
	//i.e., the distance between the locations of p and y in memory
	//in units of integers (4 bytes)
	//this distance is determined by the pointer type: in this case, int*
	auto dist = (int*)(&p) - p;
	//let's print out some interesting data:
	//the size and location of y,
	//the size and location of p (pointer to y),
	//the distance between y and p on the stack,
	//and the value when we dereference p (which should just be y)
	printf("  y (%lu) is at %p \n &y (%lu) is at %p (+%ld) \n *p = %d\n",
	sizeof(y), (void*)p, sizeof(p), (void*)&p, dist, *p);
	//this is a bit of byte manipulation to separate the 64-bit pointer p
	//into two 32-bit integers "lower" and "upper"
	//we can then print those out separately
	int lower = int(uint64(p)) & 0xFFFFFFFF;
	int upper = ((uint64(p) >> 32) & 0xFFFFFFFF);
	printf("upper = %d, lower = %d\n", lower, upper);
	//now, let's look for those two values on the stack;
	//since we already know the location of y, and the distance between y and p,
	//we should be able to find them easily
	//so let's just look through the stack and see what values we can find :{D
	for(long i = min(0, dist); i < max(0, dist + 2); i++) {
		if(i < 0) {
			printf("*(p-%ld) = %d\n", -i, *(p+i));
		} else {
			printf("*(p+%ld) = %d\n", i, *(p+i));
		}
	}
	//in fact, there will probably be two copies of the upper and lower values on the stack.
	//why might that be? ;)
}