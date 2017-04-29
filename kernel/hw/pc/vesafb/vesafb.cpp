#include "vesafb.hpp"
#include <stdint.h>
auto VESAfb::plotPixel(int x, int y, int col) -> void {
    unsigned char *lfb = (unsigned char *)((uintptr_t)(mb_info->framebuffer_addr));
    int off = y * mb_info->framebuffer_pitch / (mb_info->framebuffer_bpp / 8) + x;
    off *= mb_info->framebuffer_bpp / 8;
    for (int i = 0; i < mb_info->framebuffer_bpp / 8; i++) {
        lfb[off++] = col;
        col >>= 8;
    }
}
VESAfb::VESAfb(multiboot_info_t *mb_info)
    : mb_info(mb_info), Framebuffer(mb_info->framebuffer_width / 8, mb_info->framebuffer_height / 16) {}
VESAfb::~VESAfb() {}
