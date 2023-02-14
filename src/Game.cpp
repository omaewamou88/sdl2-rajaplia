#include <Game.h>

void Game::run()
{
    init();
    loop();
    close();
}

void Game::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Rajaplia", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    playerTexture = IMG_LoadTexture(renderer, "res/player.png");
    player = Player(playerTexture);
    platform.push_back({600.0f, 550.0f, 200.0f, 50.0f});
    platform.push_back({100.0f, 670.0f, 200.0f, 50.0f});
}

void Game::loop()
{
    unsigned int timeValue = 0;
    unsigned short deltaTime = 0;
    while(isRunning)
    {
        timeValue = SDL_GetTicks();
        input(deltaTime/1000.0f);
        update(deltaTime/1000.0f);
        render();
        deltaTime = SDL_GetTicks() - timeValue;
        if(deltaTime < 1000/FPS) SDL_Delay(1000/FPS-deltaTime);
        deltaTime = SDL_GetTicks() - timeValue;
    }
}

void Game::close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::input(float deltaTime)
{
    SDL_Event event; SDL_PollEvent(&event); if(event.type==SDL_QUIT) isRunning = false;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_ESCAPE]) isRunning = false;
    if(keystates[SDL_SCANCODE_LEFT]) player.goLeft(deltaTime, canGoLeft);
    if(keystates[SDL_SCANCODE_RIGHT]) player.goRight(deltaTime, canGoLeft);
    if(!keystates[SDL_SCANCODE_LEFT]&&!keystates[SDL_SCANCODE_RIGHT]) player.isNotWalking();
    if(keystates[SDL_SCANCODE_UP]) player.jump(isPlayerOnGround);
}

void Game::update(float deltaTime)
{
    isPlayerOnGround = false;
    canGoLeft = true;
    canGoRight = true;
    canGoUp = true;
    SDL_FPoint point{0.0f, 0.0f};

    if(player.getCollider().y>=HEIGHT-player.getCollider().h) isPlayerOnGround = true;
    for(SDL_FRect rect : platform)
    {
        for(int i = 0; i<rect.w-2; i++)
        {
            point.x = rect.x+1.0f+i;
            point.y = rect.y-1.0f;
            if(SDL_PointInFRect(&point, player.getColliderPointer()))
            {
                isPlayerOnGround = true;
                player.setPositionY(rect.y-player.getCollider().h);
            }
        }

        for(int i = 0; i<rect.w-2; i++)
        {
            point.x = rect.x+1.0f+i;
            point.y = rect.y+1.0f+rect.h;
            if(SDL_PointInFRect(&point, player.getColliderPointer()))
            {
                canGoUp = false;
                player.setPositionY(rect.y+rect.h);
            }
        }

        for(int i = 0; i<rect.h-2; i++)
        {
            point.x = rect.x-1.0f;
            point.y = rect.y+1.0f+i;
            if(SDL_PointInFRect(&point, player.getColliderPointer()))
            {
                canGoRight = false;
                player.setPositionX(rect.x-player.getCollider().w);
            }
        }

        for(int i = 0; i<rect.h-2; i++)
        {  
            point.x = rect.x+rect.w+1.0f;
            point.y = rect.y + 1.0f + i;
            if(SDL_PointInFRect(&point, player.getColliderPointer()))
            {
                canGoLeft = false;
                player.setPositionX(rect.x+rect.w-9.0f);
            }
        }
    }

    if(player.getCollider().y>HEIGHT-player.getCollider().h)
        player.setPositionY(HEIGHT-player.getCollider().h);

    player.update(deltaTime, isPlayerOnGround, canGoUp);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(SDL_FRect rect : platform) SDL_RenderFillRectF(renderer, &rect);

    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 127);
    // player.renderCollider(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    player.render(renderer);

    SDL_RenderPresent(renderer);
}