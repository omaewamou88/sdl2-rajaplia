#include <Player.h>
#define WALKING_VELOCITY 50.0f
#define GRAVITY_ACCELERATION 50.0f

Player::Player() {}

Player::Player(SDL_Texture*texture)
{
    this->texture = texture;
    this->rectangle = {600.0f, 100.0f, 13.0f*SCALE, 14.0f*SCALE};
    this->switchTexture(0);
}

SDL_FRect Player::getCollider()
{
    return rectangle;
}

void Player::render(SDL_Renderer*renderer)
{
    dst.x = rectangle.x;
    dst.y = rectangle.y;
    dst.w = src.w*SCALE;
    dst.h = src.h*SCALE;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Player::renderCollider(SDL_Renderer*renderer)
{
    SDL_RenderFillRectF(renderer, &rectangle);
}

void Player::update(float deltaTime, bool isOnGround)
{
    if(!isOnGround) gravityVelocity+=GRAVITY_ACCELERATION*deltaTime;
    else gravityVelocity = 0;

    rectangle.y+=gravityVelocity;
    if(rectangle.y>HEIGHT-rectangle.h) rectangle.y=HEIGHT-rectangle.h;
}

void Player::goLeft(float deltaTime)
{
    rectangle.x-=WALKING_VELOCITY*deltaTime;
}

void Player::goRight(float deltaTime)
{
    rectangle.x+=WALKING_VELOCITY*deltaTime;
}

void Player::switchTexture(int index)
{
    switch(index)
    {
        case 0:
            src = {1, 18, 13, 14};
            break;
    }
}