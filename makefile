all: test1

test1: test1.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -fsanitize=address,undefined -o test1 test1.cpp
	
test1_: test1.cpp
	g++ -std=c++17 -o test1 test1.cpp

clean:
	rm test1