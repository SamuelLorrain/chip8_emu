#include <cstdio>
#include <cstdlib>
#include <vector>
#include "sdl_engine.hpp"
#include "screen.hpp"

SDLEngine::SDLEngine(Screen* screen, int pixel_size) {
    if (pixel_size < 1) {
        throw "SDL engine error : pixel_size should be at least 1";
    }
    this->on_color = new SDL_Color;
    this->on_color->r = 0;
    this->on_color->g = 0;
    this->on_color->b = 0;
    this->on_color->a = 0;
    this->off_color = new SDL_Color;
    this->off_color->r = 255;
    this->off_color->g = 255;
    this->off_color->b = 255;
    this->off_color->a = 255;

    this->pixel_size = pixel_size;
    this->screen = screen;
    this->buffer_size = this->screen->get_size_x()*this->pixel_size * this->screen->get_size_y()*this->pixel_size;
    this->buffer = std::vector<uint32_t>(this->buffer_size);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }
    this->window = SDL_CreateWindow(
        "Chip8 emu",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        this->screen->get_size_x()*this->pixel_size,
        this->screen->get_size_y()*this->pixel_size,
        SDL_WINDOW_SHOWN
    );
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    this->texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING,
        this->screen->get_size_x()*this->pixel_size,
        this->screen->get_size_y()*this->pixel_size
    );
}

SDLEngine::SDLEngine(Screen* screen) : SDLEngine(screen, DEFAULT_PIXEL_SIZE) {}

SDLEngine::~SDLEngine() {
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    delete this->on_color;
    delete this->off_color;
    SDL_Quit();
}

void SDLEngine::update_display() {
    this->update_buffer_with_screen();
    SDL_UpdateTexture(
        this->texture,
        NULL,
        &this->buffer[0],
        this->buffer_size * sizeof(uint32_t)
    );
    // TODO maybe put this elsewhere
    /* SDL_RenderClear(this->renderer); */
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void SDLEngine::loop_until_quit() {
}

void SDLEngine::update_buffer_with_screen() {
    auto framebuffer = this->screen->get_framebuffer();
    for(int y = 0; y < this->screen->get_size_y(); y++) {
        for(int x = 0; x < this->screen->get_size_x(); x++) {
            if (framebuffer[(this->screen->get_size_y()*y)+x] > 0) {
                this->texture_pixel(x, y, this->on_color);
            } else {
                this->texture_pixel(x, y, this->off_color);
            }
        }
    }
    SDL_UpdateTexture(
        this->texture,
        NULL,
        &this->buffer[0],
        this->buffer_size * sizeof(uint32_t)
    );
}

void SDLEngine::texture_pixel(int x, int y, SDL_Color* color) {
    uint32_t integer_color = this->convert_sdl_color_to_uint32(color);
    int pixels_side_size = this->pixel_size / 2;
    int converted_x = x * pixels_side_size;
    int converted_y = y * pixels_side_size;
    for(int i = 1; i <= pixels_side_size; i++) {
        for(int j = 0; j < pixels_side_size; j++) {
            this->buffer[
                (this->screen->get_size_x() * (converted_y*i)) + (converted_x*j)
            ] = integer_color;
        }
    }
}

uint32_t SDLEngine::convert_sdl_color_to_uint32(SDL_Color* color) {
    SDL_PixelFormat* pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    uint32_t pixel_value = SDL_MapRGBA(pixel_format, color->r, color->g, color->b, color->a);
    SDL_FreeFormat(pixel_format);
    return pixel_value;
}
