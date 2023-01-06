CC = g++
SDL_ARGS = `pkg-config --libs --cflags sdl2`
ARGUMENTS = -g --std=c++14 -Wall ${SDL_ARGS}


chip8: build/main.o build/chip8.o build/memory.o build/cpu.o build/instruction.o build/screen.o build/sdl_engine.o
	${CC} ${ARGUMENTS} build/main.o build/chip8.o build/memory.o build/cpu.o build/instruction.o build/screen.o build/sdl_engine.o -o chip8

test: build/test_main.o build/chip8.o build/memory.o build/cpu.o build/instruction.o build/screen.o build/sdl_engine.o
	${CC} ${ARGUMENTS} build/test_main.o build/chip8.o build/memory.o build/cpu.o build/instruction.o build/screen.o build/sdl_engine.o -o test_chip8

build/test_main.o: src/main.cpp
	${CC} -c ${ARGUMENTS} src/test_main.cpp -o build/test_main.o

build/main.o: src/main.cpp
	${CC} -c ${ARGUMENTS} src/main.cpp -o build/main.o

build/chip8.o: src/chip8.cpp
	${CC} -c ${ARGUMENTS} src/chip8.cpp -o build/chip8.o

build/memory.o: src/memory.cpp
	${CC} -c ${ARGUMENTS} src/memory.cpp -o build/memory.o

build/cpu.o: src/cpu.cpp
	${CC} -c ${ARGUMENTS} src/cpu.cpp -o build/cpu.o

build/instruction.o: src/instruction.cpp
	${CC} -c ${ARGUMENTS} src/instruction.cpp -o build/instruction.o

build/screen.o: src/screen.cpp
	${CC} -c ${ARGUMENTS} src/screen.cpp -o build/screen.o

build/sdl_engine.o: src/sdl_engine.cpp
	${CC} -c ${ARGUMENTS} ${SDL_ARGS} src/sdl_engine.cpp -o build/sdl_engine.o

clean:
	rm build/*.o && rm chip8 && rm test_chip8
