#ifndef SDL_ENGINE_H
#define SDL_ENGINE_H

#include <SDL2/SDL.h>
#include <vector>
#include "screen.hpp"

constexpr int DEFAULT_PIXEL_SIZE = 8;

class SDLEngine {
    public:
        SDLEngine(Screen* screen,int pixel_size);
        SDLEngine(Screen* screen);
        ~SDLEngine();
        void update_display();
        void loop_until_quit();
    private:
        void on_pixel(int x, int y);
        void off_pixel(int x, int y);
        int pixel_size;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Color* on_color;
        SDL_Color* off_color;
        Screen* screen;
};


#endif
