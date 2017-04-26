#pragma once
#include <tty.hpp>
class CGATerm : public TTY {
    protected:
    virtual auto plotChar(int x, int y, int c) -> void;

    public:
    CGATerm();
    virtual ~CGATerm();
    virtual auto rgbSupport() -> bool;
};
