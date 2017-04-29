#pragma once
#include <tty.hpp>
/**
 * Framebuffer TTY. Has no limitations besides requiring a Framebuffer of some sort.
 * The implementation is very flexible (and thus slow). It can support every framebuffer format
 * and color format.
 */
class Framebuffer : public TTY {
    protected:
    virtual auto plotPixel(int x, int y, int col) -> void;
    virtual auto plotChar(int x, int y, int c) -> void;

    public:
    Framebuffer(int height, int width);
    virtual ~Framebuffer();
    virtual auto rgbSupport() -> bool;
};
