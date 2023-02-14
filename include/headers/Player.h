#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <tgmath.h>
#include <vector>
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
    SDL_FRect*getColliderPointer();
    void setPositionY(float y);
    void setPositionX(float x);
    void render(SDL_Renderer*renderer);
    void renderCollider(SDL_Renderer*renderer);
    void update(float deltaTime, bool isOnGround, bool canGoUp);
    void goLeft(float deltaTime, bool canGo);
    void goRight(float deltaTime, bool canGo);
    void jump(bool isOnGround);
    void isNotWalking();
    private:
    void switchTexture(int index);
    SDL_Texture*texture;
    SDL_FPoint position;
    SDL_FRect colliderRel{0.0f, 0.0f, 0.0f, 0.0f};
    SDL_FRect collider;
    SDL_Rect src;
    SDL_Rect dst;
    float gravityVelocity{0.0f};
    float jumpVar{0.0f};
    float walkAnimator{0.0f};
    bool isWalking{false};
    bool isTurnedRight{true};
    int textureIndex;
};