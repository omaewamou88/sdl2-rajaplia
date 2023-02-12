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
    if(keystates[SDL_SCANCODE_LEFT]) player.rectangle.x-=player.horizonalVelocity*deltaTime;
    if(keystates[SDL_SCANCODE_RIGHT]) player.rectangle.x+=player.horizonalVelocity*deltaTime;
    if(keystates[SDL_SCANCODE_UP]&&player.isOnGround) player.jumpState = JUMP_LENGTH;
}

void Game::update(float deltaTime)
{
    if(player.rectangle.y+player.rectangle.h>HEIGHT)
    {
        player.rectangle.y = HEIGHT-player.rectangle.h;
    }
    else if(player.rectangle.y+player.rectangle.h<HEIGHT&&player.jumpState<=0.f)
    {
        player.rectangle.y+=GRAVITATION*deltaTime;
    }

    if(player.jumpState>0.f)
    {
        player.rectangle.y-=sin((player.jumpState/JUMP_LENGTH)*(PI/2))*player.jumpPower;
        player.jumpState-=deltaTime;
    }

    if(player.rectangle.y==HEIGHT-player.rectangle.h) player.isOnGround = true;
    else player.isOnGround = false;

    std::cout << player.rectangle.x << " " << player.rectangle.y << "\n";
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRectF(renderer, &player.rectangle);
    SDL_RenderPresent(renderer);
}

Player::Player(SDL_FRect rect)
{
    rectangle = rect;
}