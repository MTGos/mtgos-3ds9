#pragma once
#include "../../framebuffer/framebuffer.hpp"
#include <multiboot.h>
class VESAfb : public Framebuffer {
    protected:
    multiboot_info_t *mb_info;
    virtual auto plotPixel(int x, int y, int col) -> void;

    public:
    VESAfb(multiboot_info_t *mb_info);
    virtual ~VESAfb();
};
