#include <Platform.h>
#define WIDTH 1200
#define HEIGHT 720
#define FPS 60

class Game
{
    public:
    void run();
    private:
    void init();
    void loop();
    void close();
    void input();
    void update(float deltaTime);
    void render();
    bool isRunning{true};
    SDL_Window*window;
    SDL_Renderer*renderer;
    SDL_Texture*playerTexture;
    SDL_Texture*tileTexture;
    std::vector<Platform> platform;
    std::vector<SDL_FRect> rects;
    Player player;
};