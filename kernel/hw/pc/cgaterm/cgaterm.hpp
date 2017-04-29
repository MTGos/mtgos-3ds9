#pragma once
#include <tty.hpp>
/**
 * TTY for a CGA terminal. Limitations: 80x25, no RGB
 */
class CGATerm : public TTY {
    protected:
    virtual auto plotChar(int x, int y, int c) -> void;

    public:
    CGATerm();
    virtual ~CGATerm();
    virtual auto rgbSupport() -> bool;
};
