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
    // TODO this code is ugly and copied right out of the arm9loaderhax git
    // find out what 90% of this does
    // Top screen
    *(volatile uint32_t *)0x10400400 = 0x000001c2;
    *(volatile uint32_t *)0x10400404 = 0x000000d1;
    *(volatile uint32_t *)0x10400408 = 0x000001c1;
    *(volatile uint32_t *)0x1040040c = 0x000001c1;
    *(volatile uint32_t *)0x10400410 = 0x00000000;
    *(volatile uint32_t *)0x10400414 = 0x000000cf;
    *(volatile uint32_t *)0x10400418 = 0x000000d1;
    *(volatile uint32_t *)0x1040041c = 0x01c501c1;
    *(volatile uint32_t *)0x10400420 = 0x00010000;
    *(volatile uint32_t *)0x10400424 = 0x0000019d;
    *(volatile uint32_t *)0x10400428 = 0x00000002;
    *(volatile uint32_t *)0x1040042c = 0x00000192;
    *(volatile uint32_t *)0x10400430 = 0x00000192;
    *(volatile uint32_t *)0x10400434 = 0x00000192;
    *(volatile uint32_t *)0x10400438 = 0x00000001;
    *(volatile uint32_t *)0x1040043c = 0x00000002;
    *(volatile uint32_t *)0x10400440 = 0x01960192;
    *(volatile uint32_t *)0x10400444 = 0x00000000;
    *(volatile uint32_t *)0x10400448 = 0x00000000;
    *(volatile uint32_t *)0x1040045C = 0x00f00190;
    *(volatile uint32_t *)0x10400460 = 0x01c100d1;
    *(volatile uint32_t *)0x10400464 = 0x01920002;
    *(volatile uint32_t *)0x10400468 = 0x18300000;
    *(volatile uint32_t *)0x10400470 = 0x80341;
    *(volatile uint32_t *)0x10400474 = 0x00010501;
    *(volatile uint32_t *)0x10400478 = 0;
    *(volatile uint32_t *)0x10400490 = 0x000002D0;
    *(volatile uint32_t *)0x1040049C = 0x00000000;

    // Disco register
    for (uint32_t i = 0; i < 256; i++) *(volatile uint32_t *)0x10400484 = 0x10101 * i;

    // Bottom screen
    *(volatile uint32_t *)0x10400500 = 0x000001c2;
    *(volatile uint32_t *)0x10400504 = 0x000000d1;
    *(volatile uint32_t *)0x10400508 = 0x000001c1;
    *(volatile uint32_t *)0x1040050c = 0x000001c1;
    *(volatile uint32_t *)0x10400510 = 0x000000cd;
    *(volatile uint32_t *)0x10400514 = 0x000000cf;
    *(volatile uint32_t *)0x10400518 = 0x000000d1;
    *(volatile uint32_t *)0x1040051c = 0x01c501c1;
    *(volatile uint32_t *)0x10400520 = 0x00010000;
    *(volatile uint32_t *)0x10400524 = 0x0000019d;
    *(volatile uint32_t *)0x10400528 = 0x00000052;
    *(volatile uint32_t *)0x1040052c = 0x00000192;
    *(volatile uint32_t *)0x10400530 = 0x00000192;
    *(volatile uint32_t *)0x10400534 = 0x0000004f;
    *(volatile uint32_t *)0x10400538 = 0x00000050;
    *(volatile uint32_t *)0x1040053c = 0x00000052;
    *(volatile uint32_t *)0x10400540 = 0x01980194;
    *(volatile uint32_t *)0x10400544 = 0x00000000;
    *(volatile uint32_t *)0x10400548 = 0x00000011;
    *(volatile uint32_t *)0x1040055C = 0x00f00140;
    *(volatile uint32_t *)0x10400560 = 0x01c100d1;
    *(volatile uint32_t *)0x10400564 = 0x01920052;
    *(volatile uint32_t *)0x10400568 = 0x18300000 + 0x46500;
    *(volatile uint32_t *)0x10400570 = 0x80301;
    *(volatile uint32_t *)0x10400574 = 0x00010501;
    *(volatile uint32_t *)0x10400578 = 0;
    *(volatile uint32_t *)0x10400590 = 0x000002D0;
    *(volatile uint32_t *)0x1040059C = 0x00000000;

    // Disco register
    for (uint32_t i = 0; i < 256; i++) *(volatile uint32_t *)0x10400584 = 0x10101 * i;

#endif
}
PICAfb::~PICAfb() {}
auto PICAfb::plotPixel(int x, int y, int col) -> void {
    unsigned char *lfb = (unsigned char *)0x18300000;
    // XXX I know it's rotated. But I need more vertical space than horizonal space.
    int off = (y * 240 + x) * 3;
    for (int i = 0; i < 3; i++) {
        lfb[off++] = col;
        col >>= 8;
    }
}
