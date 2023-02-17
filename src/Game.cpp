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
    tileTexture = IMG_LoadTexture(renderer, "res/tiles.png");
    player = Player(playerTexture);
    platform.push_back(Platform(tileTexture, {240.0f, 576.0f}, 8, 3));
}

void Game::loop()
{
    unsigned int timeValue = 0;
    unsigned short deltaTime = 0;
    while(isRunning)
    {
        timeValue = SDL_GetTicks();
        input();
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

void Game::input()
{
    SDL_Event event; SDL_PollEvent(&event); if(event.type==SDL_QUIT) isRunning = false;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_ESCAPE]) isRunning = false;
    if(keystates[SDL_SCANCODE_LEFT]) player.goLeft();
    if(keystates[SDL_SCANCODE_RIGHT]) player.goRight();
    if(keystates[SDL_SCANCODE_UP]) player.jump();
}

void Game::update(float deltaTime)
{
    float x1, y1, x2, y2;
    player.setCanGoUp(true);
    player.setCanGoDown(true);
    player.setCanGoLeft(true);
    player.setCanGoRight(true);
    // CAN GO UP
    x1 = 0.0f; y1 = 1.0f; x2 = WIDTH; y2 = 1.0f;
    if(SDL_IntersectFRectAndLine(player.getColliderPointer(), &x1, &y1, &x2, &y2))
    {
        player.setCanGoUp(false);
        player.setPositionY(0.0f);
    }
    // CAN GO DOWN
    x1 = 0.0f; y1 = HEIGHT-1.0f; x2 = WIDTH; y2 = HEIGHT-1.0f;
    if(SDL_IntersectFRectAndLine(player.getColliderPointer(), &x1, &y1, &x2, &y2))
    {
        player.setCanGoDown(false);
        player.setPositionY(HEIGHT-player.getCollider().h);
    }
    //CAN GO LEFT
    x1 = 1.0f; y1 = 0.0f; x2 = 1.0f; y2 = HEIGHT;
    if(SDL_IntersectFRectAndLine(player.getColliderPointer(), &x1, &y1, &x2, &y2))
    {
        player.setCanGoLeft(false);
        player.setPositionX(0.0f);
    }
    //CAN GO RIGHT
    x1 = WIDTH - 1.0f; y1 = 0.0f; x2 = WIDTH - 1.0f; y2 = HEIGHT;
    if(SDL_IntersectFRectAndLine(player.getColliderPointer(), &x1, &y1, &x2, &y2))
    {
        player.setCanGoRight(false);
        player.setPositionX(WIDTH-player.getCollider().w);
    }
    // LOOP
    for(Platform p : platform)
    {
        // UP
        x1 = p.getRectangle().x + 1.0f; y1 = p.getRectangle().y + p.getRectangle().h + 1.0f; x2 = p.getRectangle().x + p.getRectangle().w - 1.0f; y2 = p.getRectangle().y + p.getRectangle().h + 1.0f;
        if(SDL_IntersectFRectAndLine(player.getColliderPointer(), &x1, &y1, &x2, &y2)&&player.checkIfJumps())
        {
            player.setCanGoUp(false);
            player.setPositionY(p.getRectangle().y + p.getRectangle().h);
        }
        // DOWN
        x1 = p.getRectangle().x + 1.0f; y1 = p.getRectangle().y - 1.0f; x2 = p.getRectangle().x + p.getRectangle().w - 1.0f; y2 = p.getRectangle().y - 1.0f; 
        if(SDL_IntersectFRectAndLine(player.getColliderPointer(), &x1, &y1, &x2, &y2)&&player.chechkIfIsFalling())
        {
            player.setCanGoDown(false);
            player.setPositionY(y1-player.getCollider().h+1.0f);
        }
        // LEFT
        x1 = p.getRectangle().x + p.getRectangle().w + 1.0f; y1 = p.getRectangle().y + 1.0f; x2 = p.getRectangle().x + p.getRectangle().w + 1.0f; y2 = p.getRectangle().y + p.getRectangle().h - 1.0f;
        if(SDL_IntersectFRectAndLine(player.getColliderPointer(), &x1, &y1, &x2, &y2)&&player.checkIfGoesLeft())
        {
            player.setCanGoLeft(false);
            player.setPositionX(p.getRectangle().x + p.getRectangle().w);
        }
        // RIGHT
        x1 = p.getRectangle().x - 1.0f; y1 = p.getRectangle().y + 1.0f; x2 = p.getRectangle().x - 1.0f; y2 = p.getRectangle().y + p.getRectangle().h - 1.0f;
        if(SDL_IntersectFRectAndLine(player.getColliderPointer(), &x1, &y1, &x2, &y2)&&player.checkIfGoesRight())
        {
            player.setCanGoRight(false);
            player.setPositionX(p.getRectangle().x - player.getCollider().w);
        }
    }

    // PLAYER UPDATE
    player.update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // player.renderCollider(renderer);
    player.render(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for(Platform plat : platform) plat.render(renderer);
    SDL_RenderPresent(renderer);
}