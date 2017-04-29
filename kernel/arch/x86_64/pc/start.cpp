#include <config.h>
#include <multiboot.h>
#ifndef ENABLE_FRAMEBUFFER
#include "../../../hw/pc/cgaterm/cgaterm.hpp"
#else
#include "../../../hw/pc/vesafb/vesafb.hpp"
#endif
#include <base.hpp>
static multiboot_info_t *mb_info;
#ifndef ENABLE_FRAMEBUFFER
CGATerm term;
#else
VESAfb term(mb_info);
#endif
void main();
extern "C" void start(int eax, multiboot_info_t *ebx) {
    mb_info = ebx;
    main();
}
void drivers_init() {
    setMainTTY(&term);
    --term;
}
