#ifndef SDL_ENGINE_H
#define SDL_ENGINE_H

#include <SDL/SDL2.h>
#include <vector>

constexpr int DEFAULT_PIXEL_SIZE = 4;
constexpr SDL_Color ON_COLOR = {0, 0, 0, 0};
constexpr SDL_Color OFF_COLOR = {255, 255, 255, 255};

class SDLEngine {
    public:
        SDLEngine(Screen* screen,int pixel_size);
        SDLEngine();
        ~SDLEngine();
        void update_display();
        void loop_until_quit();
        void texture_pixel(int index, SDL_Color* color);
        inline uint32_t convert_sdl_color_to_uint32(SDL_Color* color) {
            return (this->a << 24) & (this->r << 16) & (this->g << 8) & (this->b);
        }
    private:
        void update_buffer_with_screen();
        int pixel_size;
        int buffer_size;
        vector<uint32_t> buffer;
        SDL_Window* window;
        SDL_Rendered* renderer;
        SDL_Texture* texture;
        Screen* screen;
}


#endif
