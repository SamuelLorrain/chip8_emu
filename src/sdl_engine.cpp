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
    this->on_color->r = 155;
    this->on_color->g = 155;
    this->on_color->b = 185;
    this->on_color->a = 255;
    this->off_color = new SDL_Color;
    this->off_color->r = 0;
    this->off_color->g = 0;
    this->off_color->b = 0;
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
    if(!this->window) {
        printf("SDL window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if(!this->renderer) {
        printf("SDL renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }
    if(SDL_RenderClear(this->renderer)) {
        this->handle_sdl_error();
    }
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
    this->change_pixel_color(x,y,this->on_color);
}

void SDLEngine::off_pixel(int x, int y) {
    this->change_pixel_color(x,y,this->off_color);
}

void SDLEngine::change_pixel_color(int x, int y, SDL_Color* color) {
    if(SDL_SetRenderDrawColor(
        this->renderer,
        color->r,
        color->g,
        color->b,
        color->a
    )) {
        this->handle_sdl_error();
    }
    SDL_Rect rect = {x*this->pixel_size, y*this->pixel_size, this->pixel_size, this->pixel_size};
    if(SDL_RenderFillRect(this->renderer, &rect)) {
        this->handle_sdl_error();
    }
}

void SDLEngine::handle_sdl_error() {
    printf("SDL Error : %s\n", SDL_GetError());
    delete this;
    exit(1);
}
