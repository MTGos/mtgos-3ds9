#include "picafb.hpp"
#include <config.h>
#ifdef ENABLE_SCREENINIT
#include "../mcu/mcu.hpp"
#endif
#define GL_RGBA8_OES 0
#define GL_RGB8_OES 1
#define GL_RGB565_OES 2
#define GL_RGB5_A1_OES 3
#define GL_RGBA4_OES 4
union FBFormat {
    int val;
    struct {
        char format : 3;
        char unused1 : 2;
        bool enable3D : 1;
        bool mainScreen : 1;
        bool unused2 : 1;
        char noRainbowStrip : 2;
        char unused3 : 22;
    } contents;
};
struct PDC {
    int unused1[0x17];
    int size;
    int unused2[2];
    void *leftFB[2];
    int format;
    int unused3;
    int fbselect;
    int unused4[2];
    int rainbow;
    int unused5[2];
    int stride;
    void *rightFB[2];
    int padding[2];
} __attribute__((packed));
PICAfb::PICAfb() : Framebuffer(25, 30) {
#ifdef ENABLE_SCREENINIT
    MCU::enableTopLCD();
    MCU::enableBottomLCD();
    *((uint32_t *)0x10141200) = 0x1007F; // Enable Backlights and GPU IO region
    *((uint32_t *)0x10202014) = 1;
    *((uint32_t *)0x1020200C) &= 0xFFFEFFFE;

    *((uint32_t *)0x10202240) = 0x3F; // Top screen brightness
    *((uint32_t *)0x10202A40) = 0x3F; // Bottom screen brightness
    *((uint32_t *)0x10202244) = 0x1023E;
    *((uint32_t *)0x10202A44) = 0x1023E;

    PDC *top = (PDC *)0x10400400, *bottom = (PDC *)0x10400500;
    top->unused1[0] = 0x000001c2;
    top->unused1[1] = 0x000000d1;
    top->unused1[2] = 0x000001c1;
    top->unused1[3] = 0x000001c1;
    top->unused1[4] = 0x00000000;
    top->unused1[5] = 0x000000cf;
    top->unused1[6] = 0x000000d1;
    top->unused1[7] = 0x01c501c1;
    top->unused1[8] = 0x00010000;
    top->unused1[9] = 0x0000019d;
    top->unused1[10] = 0x00000002;
    top->unused1[11] = 0x00000192;
    top->unused1[12] = 0x00000192;
    top->unused1[13] = 0x00000192;
    top->unused1[14] = 0x00000001;
    top->unused1[15] = 0x00000002;
    top->unused1[16] = 0x01960192;
    top->unused1[17] = 0x00000000;
    top->unused1[18] = 0x00000000;
    top->size = 0x00f00190; // 400*240
    top->unused2[0] = 0x01c100d1;
    top->unused2[1] = 0x01920002;
    top->leftFB[0] = (void *)0x18300000; // Beginning of VRAM
    FBFormat a;
    a.val = 0;
    a.contents.format = GL_RGB8_OES;
    a.contents.mainScreen = true;
    a.contents.noRainbowStrip = 3;
    a.val |= 0x80000;
    top->format = a.val;
    top->unused3 = 0x00010501;
    top->fbselect = 0;
    top->stride = 0x000002D0;
    top->padding[1] = 0x00000000;

    // Rainbow register
    for (uint32_t i = 0; i < 256; i++) top->rainbow = 0x10101 * i;

    bottom->unused1[0] = 0x000001c2;
    bottom->unused1[1] = 0x000000d1;
    bottom->unused1[2] = 0x000001c1;
    bottom->unused1[3] = 0x000001c1;
    bottom->unused1[4] = 0x000000cd;
    bottom->unused1[5] = 0x000000cf;
    bottom->unused1[6] = 0x000000d1;
    bottom->unused1[7] = 0x01c501c1;
    bottom->unused1[8] = 0x00010000;
    bottom->unused1[9] = 0x0000019d;
    bottom->unused1[10] = 0x00000052;
    bottom->unused1[11] = 0x00000192;
    bottom->unused1[12] = 0x00000192;
    bottom->unused1[13] = 0x0000004f;
    bottom->unused1[14] = 0x00000050;
    bottom->unused1[15] = 0x00000052;
    bottom->unused1[16] = 0x01980194;
    bottom->unused1[17] = 0x00000000;
    bottom->unused1[18] = 0x00000011;
    bottom->size = 0x00f00140; // 320*240
    bottom->unused2[0] = 0x01c100d1;
    bottom->unused2[1] = 0x01920052;
    bottom->leftFB[0] = (void *)(0x18300000 + 0x46500); // Directly at the beginning of top FB
    bottom->format = a.val;
    bottom->unused3 = 0x00010501;
    bottom->fbselect = 0;
    bottom->stride = 0x2D0;
    bottom->padding[0] = 0;

    // Rainbow register
    for (uint32_t i = 0; i < 256; i++) top->rainbow = 0x10101 * i;
#endif
}
PICAfb::~PICAfb() {}
auto PICAfb::plotPixel(int x, int y, int col) -> void {
    unsigned char *lfb = (unsigned char *)0x18300000;
    // XXX I know it's rotated. But I need more vertical space than horizonal space.
    int off = y * 240 + x;
    for (int i = 0; i < 3; i++) {
        lfb[off++] = col;
        col >>= 8;
    }
}
