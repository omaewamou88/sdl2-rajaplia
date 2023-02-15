#include <Player.h>

Player::Player() {}

Player::Player(SDL_Texture*texture)
{
    this->texture = texture;
    position = {0.0f, 0.0f};
    collider.w = 7.0f*SCALE;
    collider.h = 14.0f*SCALE;
    setState(0);
    dst.w = src.w*SCALE;
    dst.h = src.h*SCALE;
}

void Player::update(float deltaTime)
{
    // WALKING
    if(goesLeft&&canGoLeft)
    {
        position.x-=WALKING_VELOCITY*deltaTime;
        isTurnedRight = false;
        animationTimer += deltaTime;
    }
    if(goesRight&&canGoRight)
    {
        position.x+=WALKING_VELOCITY*deltaTime;
        isTurnedRight = true;
        animationTimer += deltaTime;
    }
    if(!goesLeft&&!goesRight) animationTimer = 0.0f;
    goesLeft = goesRight = false;
    // WALKING ANIMATION
    if(animationTimer>=ANIMATION_LENGTH*4) animationTimer = 0.0f;
    switch((int)(animationTimer/ANIMATION_LENGTH))
    {
        case 0: setState(0); break;
        case 1: setState(1); break;
        case 2: setState(0); break;
        case 3: setState(2); break;
    }
    // GRAVITATION
    if(canGoDown) gravityVelocity += GRAVITY_ACCELERATION*deltaTime;
    else gravityVelocity = 0.0f;
    position.y += gravityVelocity*deltaTime;
    // SETTING POSITION OF TEXTURE AND COLLIDER
    collider.x = position.x;
    collider.y = position.y;
    dst.x = position.x-(2.0f*SCALE);
    dst.y = position.y;
}

void Player::render(SDL_Renderer*renderer)
{
    if(isTurnedRight) SDL_RenderCopy(renderer, texture, &src, &dst);
    else SDL_RenderCopyEx(renderer, texture, &src, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void Player::renderCollider(SDL_Renderer*renderer)
{
    SDL_RenderFillRectF(renderer, &collider);
}

void Player::goLeft()
{
    goesLeft = true;
}

void Player::goRight()
{
    goesRight = true;
}

void Player::jump()
{
    jumpTimer = JUMP_LENGTH;
}

void Player::setPositionX(float value)
{
    position.x = value;
}

void Player::setPositionY(float value)
{
    position.y = value;
}

void Player::setCanGoUp(bool value)
{
    canGoUp = value;
}

void Player::setCanGoDown(bool value)
{
    canGoDown = value;
}

void Player::setCanGoLeft(bool value)
{
    canGoLeft = value;
}

void Player::setCanGoRight(bool value)
{
    canGoRight = value;
}

SDL_FRect Player::getCollider()
{
    return collider;
}

SDL_FRect*Player::getColliderPointer()
{
    return &collider;
}

void Player::setState(uint8_t index)
{
    switch(index)
    {
        case 0:
            src = {1, 18, 13, 14};
            break;
        case 1:
            src = {17, 17, 13, 14};
            break;
        case 2:
            src = {49, 17, 13, 14};
            break;
        case 3:
            src = {17, 65, 13, 14};
            break;
    }
}

// uint8_t Player::getState()
// {
//     if(src.x == 1 && src.y == 18) return 0;
//     else if(src.x == 17 && src.y == 17) return 1;
//     else if(src.x == 49 && src.y == 17) return 2;
//     else if(src.x == 17 && src.y == 65) return 3;
//     else
//     {
//         SDL_Log("ERROR - Player::getState() - 1");
//         return -1;
//     }
// }