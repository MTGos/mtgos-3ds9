#pragma once
#include <tty.hpp>
class Framebuffer : public TTY {
    protected:
    virtual auto plotPixel(int x, int y, int col) -> void;
    virtual auto plotChar(int x, int y, int c) -> void;

    public:
    Framebuffer(int height, int width);
    virtual ~Framebuffer();
    virtual auto rgbSupport() -> bool;
};
