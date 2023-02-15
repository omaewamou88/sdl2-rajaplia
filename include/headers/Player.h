#include <SDL.h>
#include <SDL_image.h>
#include <tgmath.h>
#include <iostream>
#include <vector>
#define WALKING_VELOCITY 200.0f
#define SCALE 3.0f
#define ANIMATION_LENGTH 0.25f
#define JUMP_LENGTH 0.5f
#define JUMP_POWER 1000.0f
#define GRAVITY_ACCELERATION 1750.0f

class Player
{
    public:
    Player();
    Player(SDL_Texture*fullTexture);
    void update(float deltaTime);
    void render(SDL_Renderer*renderer);
    void renderCollider(SDL_Renderer*renderer);
    void goLeft();
    void goRight();
    void jump();
    void setPositionX(float value);
    void setPositionY(float value);
    void setCanGoUp(bool value);
    void setCanGoDown(bool value);
    void setCanGoLeft(bool value);
    void setCanGoRight(bool value);
    SDL_FRect getCollider();
    SDL_FRect*getColliderPointer();
    private:
    void setState(uint8_t index);
    // uint8_t getState();
    SDL_Texture*texture;
    SDL_FPoint position;
    SDL_FRect collider;
    SDL_Rect src;
    SDL_Rect dst;
    float gravityVelocity{0.0f};
    float jumpTimer{0.0f};
    float animationTimer{0.0f};
    bool canGoUp{true};
    bool canGoDown{true};
    bool canGoLeft{true};
    bool canGoRight{true};
    bool goesLeft{true};
    bool goesRight{true};
    bool isTurnedRight{true};
};