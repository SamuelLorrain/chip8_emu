#ifndef SCREEN_H
#define SCREEN_H

#include <cstdint>
#include <vector>

constexpr uint8_t SCREEN_ON = 1;
constexpr uint8_t SCREEN_OFF = 0;
constexpr uint32_t SCREEN_SIZE_X = 64;
constexpr uint32_t SCREEN_SIZE_Y = 32;

class Screen {
    public:
        Screen(uint32_t size_x, uint32_t size_y);
        Screen();
        ~Screen();
        inline void on_pixel(uint32_t x, uint32_t y) {
            this->framebuffer[this->compute_framebuffer_index(x,y)] = SCREEN_ON;
        }
        inline void on_pixel(uint32_t index) {
            this->framebuffer[index] = SCREEN_ON;
        }
        inline void off_pixel(uint32_t x, uint32_t y) {
            this->framebuffer[this->compute_framebuffer_index(x,y)] = SCREEN_OFF;
        }
        inline void off_pixel(uint32_t index) {
            this->framebuffer[index] = SCREEN_OFF;
        }
        inline std::vector<uint8_t>& get_framebuffer() {
            return this->framebuffer;
        }
        inline uint32_t get_size_x() {
            return this->size_x;
        }
        inline uint32_t get_size_y() {
            return this->size_y;
        }
        inline uint32_t get_size() {
            return this->size_x * this->size_y;
        }
        inline uint8_t get_pixel(uint32_t x, uint32_t y) {
            return this->framebuffer[this->compute_framebuffer_index(x,y)];
        }
        
    private:
        inline uint32_t compute_framebuffer_index(uint32_t x, uint32_t y) {
            return ((this->size_x * y) + x);
        }

        uint32_t size_x;
        uint32_t size_y;
        std::vector<uint8_t> framebuffer;
};

#endif
