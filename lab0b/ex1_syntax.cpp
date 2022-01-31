#include <cstdio>
#include <cstdlib>

//this is an extremely simple struct, with two public members
struct test_struct {
	int x;
	int y;
};

test_struct create_test_struct(int x, int y) {
	//method 1: create a blank struct and fill in the data afterwards
	test_struct t1;
	t1.x = x;
	t1.y = y;
	//method 2: create a struct by filling in the data in order of declaration
	test_struct t2{x, y};
	//we can also create one on the heap
	test_struct* t3 = new test_struct{x, y};
	//but be sure to delete it afterwards
	delete t3;
	//be sure you return something!
	return t1;
}

//this is a simple class, showing how different access levels are labeled
//for different member variables and functions
class test_class {

	//by default, everything in a class is private;
	//so, until you put a "public:" label,
	//everything will be private.

	int x; //this is private

	//now, everything after this will be public
	//until another access label is inserted.
	public:

	int y; //this is public

	//this is public
	test_class(int val) : x(val), y(val + 1) {}

	//this is public
	int getX() {
		return x;
	}

	//with another private access label, everything afterwards will now be private
	private:

	//this is private
	void setX(int x) {
		//important note!
		//"this", which refers to the current object,
		//is a pointer!
		//this means we must use the arrow operator to refer to its members.
		this->x = x;
		//alternatively, we could do something like:
		//(*this).x = x;
	}
};

test_class* create_test_class() {
	//let's just create one that will have x=1, y=2
	test_class t(1);
	//y is public, and we have an object, so
	//we can directly access it 
	t.y = 3;
	//let's get a pointer to t
	test_class* tpointer = &t;
	//again, these are our two pointer access methods:
	//either dereference with * and then use .
	//or use ->
	(*tpointer).y = tpointer->getX();
	//though, technically, there is a third method...
	//we can treat tpointer as a single-element array:
	tpointer[0].y = 4;
	//careful!
	//"t" lives on the stack, so it'll be deleted when this function returns
	//so if we return a pointer to it,
	//it'll be invalid!
	return tpointer;
}

//we're going to use typedef to give "unsigned long long"
//the nickname "Jimmy"
//so now whenever we say "Jimmy",
//we'll be referring to "unsigned long long"
//it's just a bit shorter to write :)
typedef unsigned long long Jimmy;

int main (int argc, char** argv) {

	printf("test run with %d cmdline arguments\n", argc);

	//thanks to the above typedef, these mean the same thing
	unsigned long long x1 = 1234;
	Jimmy x2 = 1234;

	create_test_struct(3, 4);
	create_test_class();

	//this is a c-string,
	//a null-terminated array of characters
	//if you hover over the "hello" in vscode,
	//it'll say (const char[6])"hello"
	//this means that it is an array of length 6.
	//"hello" is only 5 characters - the 6th is a 0.
	//in memory, it looks like:
	//['h', 'e', 'l', 'l', 'o', 0]
	const char* string = "hello";

	//always be sure to return something :)
	return 0;
}