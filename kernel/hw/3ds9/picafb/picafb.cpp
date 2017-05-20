#include "picafb.hpp"
#include <config.h>
PICAfb::PICAfb() : Framebuffer(40, 15) {}
PICAfb::~PICAfb() {}
auto PICAfb::plotPixel(int x, int y, int col) -> void {
    unsigned char *lfb = (unsigned char *)0x18300000 + 0x46500;
    y=240-y-1;
    int off = (x * 240 + y) * 3;
    for (int i = 0; i < 3; i++) {
        lfb[off++] = col;
        col >>= 8;
    }
}
