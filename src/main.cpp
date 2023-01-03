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

    bool quit = false;
    SDL_Event e;
    while( !quit )
    {
        chip8->next();
        sdl_engine->update_display();
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        SDL_Delay(100);
    }

    delete memory;
    delete cpu;
    delete screen;
    delete chip8;
    delete sdl_engine;
    return 0;
}
