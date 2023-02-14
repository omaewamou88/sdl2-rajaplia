#include <Player.h>
#define WALKING_VELOCITY 200.0f
#define GRAVITY_ACCELERATION 50.0f
#define JUMP_POWER 750.0f
#define JUMP_TIME 0.5f
#define WALK_ANIMATION_LENGHT 0.25f

Player::Player() {}

Player::Player(SDL_Texture*texture)
{
    this->texture = texture;
    this->position = {600.0f, 100.0f};
    this->switchTexture(0);
    this->collider.x = this->position.x;
    this->collider.y = this->position.y;
    colliderRel = {2.0f*SCALE, 0.0f*SCALE, 7.0f*SCALE, 14.0f*SCALE};
    collider.w = colliderRel.w;
    collider.h = colliderRel.h;
}

SDL_FRect Player::getCollider()
{
    return collider;
}

SDL_FRect*Player::getColliderPointer()
{
    return &collider;
}

void Player::setPositionY(float y)
{
    position.y = y;
}

void Player::setPositionX(float x)
{
    position.x = x;
}

void Player::render(SDL_Renderer*renderer)
{
    dst.x = position.x;
    dst.y = position.y;
    dst.w = src.w*SCALE;
    dst.h = src.h*SCALE;
    if(isTurnedRight) SDL_RenderCopy(renderer, texture, &src, &dst);
    else SDL_RenderCopyEx(renderer, texture, &src, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void Player::renderCollider(SDL_Renderer*renderer)
{
    SDL_RenderFillRectF(renderer, &collider);
}

void Player::update(float deltaTime, bool isOnGround, bool canGoUp)
{
    if(!isOnGround&&jumpVar<=0.0f) gravityVelocity+=GRAVITY_ACCELERATION*deltaTime;
    else gravityVelocity = 0;

    position.y+=gravityVelocity;

    if(!canGoUp) jumpVar = 0.0f;

    if(jumpVar>0.0f)
    {
        jumpVar-=deltaTime;
        position.y-=JUMP_POWER*sin((jumpVar/JUMP_TIME)*(PI/2))*deltaTime;
    }

    if(isTurnedRight) collider.x = position.x + colliderRel.x;
    else collider.x = position.x + colliderRel.x + SCALE;
    collider.y = position.y + colliderRel.y;

    if(isWalking)
    {
        walkAnimator += deltaTime;
        if(walkAnimator<WALK_ANIMATION_LENGHT)
        {
            if(textureIndex!=0) switchTexture(0);
        } else if(walkAnimator>=WALK_ANIMATION_LENGHT&&walkAnimator<WALK_ANIMATION_LENGHT*2)
        {
            if(textureIndex!=1) switchTexture(1);
        } else if(walkAnimator>=WALK_ANIMATION_LENGHT*2&&walkAnimator<WALK_ANIMATION_LENGHT*3)
        {
            if(textureIndex!=2) switchTexture(2);
        } else if(walkAnimator>WALK_ANIMATION_LENGHT*3)
        {
            walkAnimator = 0.0f;
            if(textureIndex!=0) switchTexture(0);
        }
    } else if(textureIndex!=0) switchTexture(0);

    if(!isOnGround)
    {
        if(textureIndex!=3) switchTexture(3);
    }
}

void Player::goLeft(float deltaTime, bool canGo)
{
    if(canGo)
    {
    position.x-=WALKING_VELOCITY*deltaTime;
    isTurnedRight = false;
    isWalking = true;
    }
}

void Player::goRight(float deltaTime, bool canGo)
{
    if(canGo)
    {
    position.x+=WALKING_VELOCITY*deltaTime;
    isTurnedRight = true;
    isWalking = true;
    }
}

void Player::isNotWalking()
{
    isWalking = false;
}

void Player::jump(bool isOnGround)
{
    if(isOnGround) jumpVar = JUMP_TIME;
}

void Player::switchTexture(int index)
{
    switch(index)
    {
        case 0:
            textureIndex = 0;
            src = {1, 18, 13, 14};
            break;
        case 1:
            textureIndex = 1;
            src = {17, 17, 13, 14};
            break;
        case 2:
            textureIndex = 2;
            src = {49, 17, 13, 14};
            break;
        case 3:
            textureIndex =3;
            src = {17, 65, 13, 14};
            break;
    }
}