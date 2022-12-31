#include <cstdio>
#include <cstdlib>
#include <vector>
#include "sdl_engine.hpp"

SDLEngine(Screen* screen, int pixel_size) {
    if (pixel_size < 1) {
        throw "SDL engine error : pixel_size should be at least 1";
    }
    this->pixel_size = pixel_size;
    this->screen = screen;
    this->buffer_size = screen->get_size_x()*this->pixel_size * screen->get_size_y()*this->pixel_size;
    this->buffer = vector(this->buffer_size);
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }
    this->window = SDL_CreateWindow(
        "SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screen->get_size_x()*this->pixel_size,
        screen->get_size_y()*this->pixel_size,
        SDL_WINDOW_SHOWN
    );
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    this->texture = SDL_CreateTexture(
        render,
        SDL_PIXELFORMAT_RGB888, 
        SDL_TEXTUREACCESS_STATIC, // TODO test streaming
        screen->get_size_x()*this->pixel_size,
        screen->get_size_y()*this->pixel_size
    );
}

SDLEngine(Screen* screen) : SDLEngine(screen, DEFAULT_PIXEL_SIZE) {}

~SDLEngine() {
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void SDLEngine::update_display() {
    this->update_buffer_with_screen();
    SDL_UpdateTexture(
        this->texture,
        NULL,
        this->buffer,
        this->buffer_size * sizeof(uint32_t)
    );
    // TODO maybe put this elsewhere
    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}

void SDLEngine::loop_until_quit() {
    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}

void SDLEngine::update_buffer_with_screen() {
    auto framebuffer = this->screen->get_framebuffer();
    int screen_size = this->screen->get_size();
    for(int y = 0; y < this->screen->get_size_y(); y++) {
        for(int x = 0; x < this->screen->get_size_x(); x++) {
            if (framebuffer[(this->get_size_y()*y)+x] > 0) {
                this->assign_pixel_buffer(x, y, ON_COLOR);
            } else {
                this->assign_pixel_buffer(x, y, OFF_COLOR);
            }
        }
    }
    SDL_UpdateTexture(
        this->texture,
        NULL,
        this->buffer,
        this->buffer_size * sizeof(uint32_t)
    )
}

void SDLEngine::assign_pixel_buffer(int x, int y, SDL_Color* color) {
    uint32_t integer_color = this->convert_sdl_color_to_uint32(color);
    int pixels_side_size = this->pixel_size / 2;
    int converted_x = x * pixels_side_size;
    int converted_y = y * pixels_side_size;
    for(int i = 1; i <= pixels_size_size; i++) {
        for(int j = 0; j < pixels_size_size; j++) {
            this->buffer[
                (this->screen->get_size_x() * (converted_y*i)) + (converted_x*j)
            ] = integer_color;
        }
    }
}
