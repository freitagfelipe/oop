compiler_flags = -Wall -Werror -Wextra -Iinclude

all: main.o
	g++ main.o -o main

main.o:
	g++ main.cpp -c ${compiler_flags}

clear:
ifeq ($(OS), Windows_NT) 
	del *.o
else
	rm *.o
endif