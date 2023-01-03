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
    this->on_color->r = 255;
    this->on_color->g = 0;
    this->on_color->b = 0;
    this->on_color->a = 255;
    this->off_color = new SDL_Color;
    this->off_color->r = 255;
    this->off_color->g = 255;
    this->off_color->b = 255;
    this->off_color->a = 0;

    this->pixel_size = pixel_size;
    this->screen = screen;
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
    SDL_RenderClear(this->renderer);
}

SDLEngine::SDLEngine(Screen* screen) : SDLEngine(screen, DEFAULT_PIXEL_SIZE) {}

SDLEngine::~SDLEngine() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    delete this->on_color;
    delete this->off_color;
    SDL_Quit();
}

void SDLEngine::update_display() {
    for(int y = 0;  y < this->screen->get_size_y(); y++) {
        for(int x = 0;  x < this->screen->get_size_x(); x++) {
            if (this->screen->get_framebuffer()[(this->screen->get_size_x() * y) + x] > 0) {
                this->on_pixel(x,y);
            } else {
                this->off_pixel(x,y);
            }
        }
    }
    SDL_RenderPresent(this->renderer);
}

void SDLEngine::on_pixel(int x, int y) {
    SDL_SetRenderDrawColor(
            this->renderer,
            this->on_color->r,
            this->on_color->g,
            this->on_color->b,
            this->on_color->a
    );
    SDL_Rect rect = {x*this->pixel_size, y*this->pixel_size, this->pixel_size, this->pixel_size};
    SDL_RenderFillRect(this->renderer, &rect);

}

void SDLEngine::off_pixel(int x, int y) {
    SDL_SetRenderDrawColor(
            this->renderer,
            this->off_color->r,
            this->off_color->g,
            this->off_color->b,
            this->off_color->a
    );
    SDL_Rect rect = {x*this->pixel_size, y*this->pixel_size, this->pixel_size, this->pixel_size};
    SDL_RenderFillRect(this->renderer, &rect);
}
