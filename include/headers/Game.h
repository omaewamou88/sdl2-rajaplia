#include <SDL.h>
#include <iostream>
#include <tgmath.h>
#define WIDTH 1280
#define HEIGHT 720
#define FPS 60
#define GRAVITATION 500
#define PI 3.14159f
#define JUMP_LENGTH 1.f

struct Player
{
    Player(SDL_FRect rect);
    SDL_FRect rectangle;
    float horizonalVelocity{100.0f};
    float jumpState{0.f};
    float jumpPower{10.0f};
    bool isOnGround{false};
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
    Player player{{615.f, 100.f, 50.f, 50.f}};
};