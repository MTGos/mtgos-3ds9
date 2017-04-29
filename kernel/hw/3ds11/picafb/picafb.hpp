#pragma once
#include "../../framebuffer/framebuffer.hpp"
/**
 * Framebuffer for the 3ds
 */
class PICAfb : public Framebuffer {
    protected:
    virtual auto plotPixel(int x, int y, int col) -> void;

    public:
    PICAfb();
    virtual ~PICAfb();
};
