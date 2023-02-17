#include <Platform.h>
#define TS 16

Platform::Platform(SDL_Texture*texture, SDL_FPoint position, uint8_t width, uint8_t height) 
: texture(texture), position(position), width(width), height(height)
{
    uint8_t mh = height-1; uint8_t wh = width-1;
    for(int i=0; i<height; i++) for(int j=0; j<width; j++)
    {
        if(j==0&&i==0) src.push_back({0, 0, TS, TS});
        else if(j>0&&j<wh&&i==0) src.push_back({TS*(1+j%3), 0, TS, TS});
        else if(j==wh&&i==0) src.push_back({TS*4, 0, TS, TS});
        else if(j==0&&i>0&&i<mh) src.push_back({0, TS*(1+i%3), TS, TS});
        else if(j>0&&j<wh&&i>0&&i<mh) src.push_back({1, 1, 1, 1});
        else if(j==wh&&i>0&&i<mh) src.push_back({TS*4, TS*(1+i%3), TS, TS});
        else if(j==0&&i==mh) src.push_back({0, TS*4, TS, TS});
        else if(j>0&&j<wh&&i==mh) src.push_back({TS*(1+j%3), TS*4, TS, TS});
        else if(j==wh&&i==mh) src.push_back({TS*4, TS*4, TS, TS});
    }
    for(SDL_Rect rect : src) std::cout << rect.x << " " << rect.y << "\n";
}

void Platform::render(SDL_Renderer*renderer)
{
    dst.w = dst.h = TS*SCALE;
    uint8_t n = 0;
    for(int i=0; i<height; i++) for(int j=0; j<width; j++)
    {
        dst.x = position.x + j*TS*SCALE;
        dst.y = position.y + i*TS*SCALE;
        SDL_RenderCopy(renderer, texture, &src[n], &dst);
        n++;
    }
}

SDL_FRect Platform::getRectangle()
{   
    return {position.x, position.y, width*TS*SCALE, height*TS*SCALE};
}