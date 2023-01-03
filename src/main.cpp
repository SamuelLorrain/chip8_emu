#include <iostream>
#include "chip8.hpp"
#include "memory.hpp"
#include "cpu.hpp"
#include "instruction.hpp"
#include "sdl_engine.hpp"

int main(int argc, char** argv) {
    std::cout << "chip8..." << std::endl;
    Memory* memory = new Memory();
    Cpu* cpu = new Cpu();
    Screen* screen = new Screen();
    Chip8* chip8 = new Chip8(memory, cpu, screen);
    SDLEngine* sdl_engine = new SDLEngine(screen);
    if (argc < 2) {
        std::cout << "Please provide path to ROM as argument" << std::endl;
        return 1;
    }

    chip8->load_rom(argv[1]);

    uint8_t keymap[16] = {
        SDLK_1,
        SDLK_2,
        SDLK_3,
        SDLK_4,
        SDLK_a,
        SDLK_z,
        SDLK_e,
        SDLK_r,
        SDLK_q,
        SDLK_s,
        SDLK_d,
        SDLK_f,
        SDLK_w,
        SDLK_x,
        SDLK_c,
        SDLK_v,
    };

    bool quit = false;
    SDL_Event e;
    while( !quit )
    {
        chip8->next();
        while(SDL_PollEvent( &e ) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            if(e.type == SDL_KEYDOWN) {
                for (int i = 0; i < 16; ++i) {
                    if (e.key.keysym.sym == keymap[i]) {
                        chip8->get_keys()[i] = 1;
                    }
                }
            }
            if(e.type == SDL_KEYUP) {
                for (int i = 0; i < 16; ++i) {
                    if (e.key.keysym.sym == keymap[i]) {
                        chip8->get_keys()[i] = 0;
                    }
                }
            }
        }
        sdl_engine->update_display();
        SDL_Delay(10);
    }

    delete memory;
    delete cpu;
    delete screen;
    delete chip8;
    delete sdl_engine;
    return 0;
}
