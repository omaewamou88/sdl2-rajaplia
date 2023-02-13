#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <tgmath.h>
#define WIDTH 1280
#define HEIGHT 720
#define FPS 60
#define PI 3.14159f
#define SCALE 3.0f

class Player
{
    public:
    Player();
    Player(SDL_Texture*texture);
    SDL_FRect getCollider();
    void render(SDL_Renderer*renderer);
    void renderCollider(SDL_Renderer*renderer);
    void update(float deltaTime, bool isOnGround);
    void goLeft(float deltaTime);
    void goRight(float deltaTime);
    private:
    void switchTexture(int index);
    SDL_Texture*texture;
    SDL_FRect rectangle;
    SDL_Rect src;
    SDL_Rect dst;
    float gravityVelocity{0.0f};
};