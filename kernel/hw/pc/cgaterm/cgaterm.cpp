#include "cgaterm.hpp"
#include "cp437.hpp"
CGATerm::CGATerm() : TTY(80, 25) {}
CGATerm::~CGATerm() {}
auto CGATerm::rgbSupport() -> bool { return false; }
struct ScreenChar {
    unsigned char ch;
    char fgcolor : 4;
    char bgcolor : 4;
} __attribute__((packed));
ScreenChar *scr = (ScreenChar *)0xB8000;
auto CGATerm::plotChar(int x, int y, int c) -> void {
    char ch = unicodeToCP437(c);
    scr[y * 80 + x].ch = ch;
    scr[y * 80 + x].bgcolor = 0;
    char col = 0;
    switch (curColor) {
    case Color::BLACK: col = 0; break;
    case Color::BLUE: col = 1; break;
    case Color::GREEN: col = 2; break;
    case Color::CYAN: col = 3; break;
    case Color::RED: col = 4; break;
    case Color::MAGENTA: col = 5; break;
    case Color::BROWN: col = 6; break;
    case Color::LIGHT_GRAY: col = 7; break;
    case Color::GRAY: col = 8; break;
    case Color::LIGHT_BLUE: col = 9; break;
    case Color::LIGHT_GREEN: col = 10; break;
    case Color::LIGHT_CYAN: col = 11; break;
    case Color::LIGHT_RED: col = 12; break;
    case Color::LIGHT_MAGENTA: col = 13; break;
    case Color::YELLOW: col = 14; break;
    case Color::WHITE: col = 15; break;
    }
    scr[y * 80 + x].fgcolor = col;
}
