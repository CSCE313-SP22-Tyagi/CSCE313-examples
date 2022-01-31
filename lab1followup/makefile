all: ex1 ex2 ex3 ex4

ex1: ex1_filedescriptors.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -o ex1 ex1_filedescriptors.cpp

ex2: ex2_filedescriptors_pipe.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -o ex2 ex2_filedescriptors_pipe.cpp

ex3: ex3_stackcorruption.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -o ex3 ex3_stackcorruption.cpp

ex4: ex4_eof.cpp
	g++ -std=c++17 -pedantic -Wall -Wextra -o ex4 ex4_eof.cpp
	
clean:
	rm ex1 ex2 ex3 ex4