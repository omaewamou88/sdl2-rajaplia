#include <Player.h>

class Platform
{
    public:
    Platform(SDL_Texture*texture, SDL_FPoint position, uint8_t width, uint8_t height);
    void render(SDL_Renderer*renderer);
    SDL_FRect getRectangle();
    private:
    const SDL_FPoint position;
    SDL_Texture*texture;
    const uint8_t width{0};
    const uint8_t height{0};
    std::vector<SDL_Rect> src;
    SDL_Rect dst;
};