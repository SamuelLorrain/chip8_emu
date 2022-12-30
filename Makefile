CC = g++
ARGUMENTS = -c --std=c++14 -Wall


chip8: build/main.o build/chip8.o build/memory.o build/cpu.o build/instruction.o build/screen.o
	${CC} build/main.o build/chip8.o build/memory.o build/cpu.o build/instruction.o build/screen.o -o chip8

test: build/test_main.o build/chip8.o build/memory.o build/cpu.o build/instruction.o build/screen.o
	${CC} build/test_main.o build/chip8.o build/memory.o build/cpu.o build/instruction.o build/screen.o -o test_chip8

build/test_main.o: src/main.cpp
	${CC} ${ARGUMENTS} src/test_main.cpp -o build/test_main.o

build/main.o: src/main.cpp
	${CC} ${ARGUMENTS} src/main.cpp -o build/main.o

build/chip8.o: src/chip8.cpp
	${CC} ${ARGUMENTS} src/chip8.cpp -o build/chip8.o

build/memory.o: src/memory.cpp
	${CC} ${ARGUMENTS} src/memory.cpp -o build/memory.o

build/cpu.o: src/cpu.cpp
	${CC} ${ARGUMENTS} src/cpu.cpp -o build/cpu.o

build/instruction.o: src/instruction.cpp
	${CC} ${ARGUMENTS} src/instruction.cpp -o build/instruction.o

build/screen.o: src/screen.cpp
	${CC} ${ARGUMENTS} src/screen.cpp -o build/screen.o

clean:
	rm build/*.o && rm chip8 && rm test_chip8
