all:
	g++ -Iinclude/SDL2 -Iinclude/headers -Llib -o prog src/Main.cpp src/Game.cpp src/Player.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image