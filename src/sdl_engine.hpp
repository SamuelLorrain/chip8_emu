#ifndef SDL_ENGINE_H
#define SDL_ENGINE_H

#include <SDL2/SDL.h>
#include <vector>
#include "screen.hpp"

constexpr int DEFAULT_PIXEL_SIZE = 4;

class SDLEngine {
    public:
        SDLEngine(Screen* screen,int pixel_size);
        SDLEngine(Screen* screen);
        ~SDLEngine();
        void update_display();
        void loop_until_quit();
    private:
        void update_buffer_with_screen();
        inline uint32_t convert_sdl_color_to_uint32(SDL_Color* color) {
            return (color->a << 24) & (color->r << 16) & (color->g << 8) & (color->b);
        }
        void texture_pixel(int x, int y, SDL_Color* color);
        int pixel_size;
        int buffer_size;
        std::vector<uint32_t> buffer;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Color* on_color;
        SDL_Color* off_color;
        Screen* screen;
};


#endif
