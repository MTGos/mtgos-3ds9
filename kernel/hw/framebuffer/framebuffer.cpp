#include "framebuffer.hpp"
#include <genfont.h>
auto Framebuffer::plotPixel(int x, int y, int col) -> void {}
auto Framebuffer::plotChar(int x, int y, int c) -> void {
    if (c > 65535) return;
    int width = font_widths[c];
    if (width == 16) this->x++;
    if (!width) return;
    int color;
    for (int px = x * 8; px < (x * 8) + width; px++)
        for (int py = y * 16; py < (y * 16) + 16; py++) {
            color = rgbColor;
            if (!useRGB) {
                switch (curColor) {
                case Color::BLACK: color = 0x000000; break;
                case Color::BLUE: color = 0x0000AA; break;
                case Color::GREEN: color = 0x00AA00; break;
                case Color::CYAN: color = 0x00AAAA; break;
                case Color::RED: color = 0xAA0000; break;
                case Color::MAGENTA: color = 0xAA00AA; break;
                case Color::BROWN: color = 0xAA5500; break;
                case Color::LIGHT_GRAY: color = 0xAAAAAA; break;
                case Color::GRAY: color = 0x555555; break;
                case Color::LIGHT_BLUE: color = 0x5555FF; break;
                case Color::LIGHT_GREEN: color = 0x55FF55; break;
                case Color::LIGHT_CYAN: color = 0x55FFFF; break;
                case Color::LIGHT_RED: color = 0xFF5555; break;
                case Color::LIGHT_MAGENTA: color = 0xFF55FF; break;
                case Color::YELLOW: color = 0xFFFF55; break;
                case Color::WHITE: color = 0xFFFFFF; break;
                }
                rgbColor = color;
                useRGB = true;
            }
            unsigned char *chara = (unsigned char *)font_ptr[c];
            int bx = px - (x * 8);
            int by = py - (y * 16);
            if (width == 16) {
                by *= 2;
                if (bx > 7) {
                    by++;
                    bx -= 8;
                }
                plotPixel(px, py, (chara[by] & (1 << (7 - bx))) ? color : 0);
            } else {
                plotPixel(px, py, (chara[by] & (1 << (7 - bx))) ? color : 0);
            }
        }
}
Framebuffer::Framebuffer(int height, int width) : TTY(height, width) {}
Framebuffer::~Framebuffer() {}
auto Framebuffer::rgbSupport() -> bool { return true; }
