#pragma once
#include "../../framebuffer/framebuffer.hpp"
class PICAfb : public Framebuffer {
    protected:
    virtual auto plotPixel(int x, int y, int col) -> void;

    public:
    PICAfb();
    virtual ~PICAfb();
};
