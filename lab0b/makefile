all: ex1 ex2 ex3

ex1: ex1_syntax.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -fsanitize=address,undefined -o ex1 ex1_syntax.cpp
	
ex2: ex2_memcpy.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -fsanitize=address,undefined -o ex2 ex2_memcpy.cpp
	
ex3: ex3_pointers.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -o ex3 ex3_pointers.cpp
	
clean:
	rm ex1 ex2 ex3