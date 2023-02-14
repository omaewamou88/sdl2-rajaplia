#include <Player.h>

class Game
{
    public:
    void run();
    private:
    void init();
    void loop();
    void close();
    void input(float deltaTime);
    void update(float deltaTime);
    void render();
    bool isRunning{true};
    bool isPlayerOnGround{false};
    bool canGoRight{true};
    bool canGoLeft{true};
    bool canGoUp{true};
    SDL_Window*window;
    SDL_Renderer*renderer;
    SDL_Texture*playerTexture;
    Player player;
    std::vector<SDL_FRect> platform;
};