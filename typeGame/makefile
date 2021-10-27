compiler_flags = -Wall -Werror -Wextra -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: main.o game.o board.o bubble.o pencil.o end.o menu.o cursor.o audio.o
	g++ main.o game.o board.o bubble.o pencil.o end.o menu.o cursor.o audio.o ${compiler_flags} -o main && ./main

clear:
	rm *.o

main.o: main.cpp
	g++ main.cpp -c ${compiler_flags}

game.o: game/game.cpp game/game.hpp
	g++ game/game.cpp -c ${compiler_flags}

board.o: board/board.cpp board/board.hpp
	g++ board/board.cpp -c ${compiler_flags}

bubble.o: bubble/bubble.cpp bubble/bubble.hpp
	g++ bubble/bubble.cpp -c ${compiler_flags}

pencil.o: pencil/pencil.cpp pencil/pencil.hpp
	g++ pencil/pencil.cpp -c ${compiler_flags}

end.o: end/end.cpp end/end.hpp
	g++ end/end.cpp -c ${compiler_flags}

menu.o: menu/menu.cpp menu/menu.hpp
	g++ menu/menu.cpp -c ${compiler_flags}

cursor.o: cursor/cursor.cpp cursor/cursor.hpp
	g++ cursor/cursor.cpp -c ${compiler_flags}

audio.o: audio/audio.cpp audio/audio.hpp
	g++ audio/audio.cpp -c ${compiler_flags}