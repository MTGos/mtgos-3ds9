#include "picafb.hpp"
#include <config.h>
PICAfb::PICAfb() : Framebuffer(25, 20) {}
PICAfb::~PICAfb() {}
auto PICAfb::plotPixel(int x, int y, int col) -> void {
    unsigned char *lfb = (unsigned char *)0x18300000 + 0x46500;
    // XXX I know it's rotated. But I need more vertical space than horizonal space.
    int off = (y * 240 + x) * 3;
    for (int i = 0; i < 3; i++) {
        lfb[off++] = col;
        col >>= 8;
    }
}
