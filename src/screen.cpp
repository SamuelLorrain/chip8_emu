#include "screen.hpp"
#include <vector>

Screen::Screen(uint32_t size_x, uint32_t size_y) {
    this->size_x = size_x;
    this->size_y = size_y;
    this->framebuffer = std::vector<uint8_t>(this->size_x * this->size_y);
}

Screen::Screen() : Screen(SCREEN_SIZE_X, SCREEN_SIZE_Y) {}

Screen::~Screen() {}
