#include "vesafb.hpp"
#include <stdint.h>
auto VESAfb::plotPixel(int x, int y, int col) -> void {
    int *lfb = (int *)((uintptr_t)(mb_info->framebuffer_addr));
    lfb[y * mb_info->framebuffer_pitch + x] = col;
}
VESAfb::VESAfb(multiboot_info_t *mb_info)
    : mb_info(mb_info), Framebuffer(mb_info->framebuffer_width / 8, mb_info->framebuffer_height / 16) {}
VESAfb::~VESAfb() {}
