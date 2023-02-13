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
    playerTexture = IMG_LoadTexture(renderer, "res/player.png");
    player = Player(playerTexture);
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
    if(keystates[SDL_SCANCODE_LEFT]) player.goLeft(deltaTime);
    if(keystates[SDL_SCANCODE_RIGHT]) player.goRight(deltaTime);
}

void Game::update(float deltaTime)
{
    bool isPlayerOnGround = true;
    if(player.getCollider().y<HEIGHT-player.getCollider().h) isPlayerOnGround = false;
    player.update(deltaTime, isPlayerOnGround);
}

void Game::render()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 127);
    player.renderCollider(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    player.render(renderer);
    SDL_RenderPresent(renderer);
}