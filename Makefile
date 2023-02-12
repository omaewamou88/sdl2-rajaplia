all:
	g++ -Iinclude/SDL2 -Iinclude/headers -Llib -o prog src/Main.cpp src/Game.cpp -lmingw32 -lSDL2main -lSDL2