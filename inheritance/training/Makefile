compiler_flags = -Wall -Werror -Wextra -Iincludes

all: main.o person.o worker.o developer.o
	g++ main.o person.o worker.o developer.o -o main

main.o: main.cpp
	g++ main.cpp -c ${compiler_flags}

person.o: source/person.cpp includes/person.hpp
	g++ source/person.cpp -c ${compiler_flags}

worker.o: source/worker.cpp includes/worker.hpp
	g++ source/worker.cpp -c ${compiler_flags}

developer.o: source/developer.cpp includes/developer.hpp
	g++ source/developer.cpp -c ${compiler_flags}

clear:
ifeq ($(OS), Windows_NT) 
	del *.o
else
	rm *.o
endif