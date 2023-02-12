#include <SDL.h>
#include <iostream>
#define WIDTH 1280
#define HEIGHT 720
#define FPS 60
#define GRAVITATION 750
#define VELOCITY 100

struct Player
{
    Player(SDL_FRect rect);
    SDL_FRect rectangle;
};

class Game
{
    public:
    void run();
    private:
    void init();
    void loop();
    void close();
    void input(float deltaTime);
    void update(float deltaTime);
    void render();
    bool isRunning{true};
    SDL_Window*window;
    SDL_Renderer*renderer;
    Player player{{100.f, 100.f, 100.f, 100.f}};
};