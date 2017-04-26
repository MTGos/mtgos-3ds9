#pragma once
#include <kobject.hpp>
enum class Color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
};
class TTY : public Kobject {
    protected:
    int x;
    int y;
    int width;
    int height;
    Color curColor;
    unsigned int rgbColor;
    bool useRGB;
    virtual auto plotChar(int x, int y, int c) -> void;

    public:
    TTY(int width, int height);
    virtual ~TTY();
    virtual auto rgbSupport() -> bool;
    virtual auto setColor(Color c) -> void;
    virtual auto setColor(unsigned int c) -> void;
    virtual auto putChar(int c) -> void;
    virtual auto puts(const char *s) -> void;
    template <typename T>
    auto puti(T x) -> TTY & {
        T output = x;
        const char *chars = "0123456789ABCDEF";
        char buf[sizeof(T) * 8 + 1];
        buf[sizeof(T) * 8] = '\0';
        char *ptr = buf + sizeof(T) * 8 - 1;
        do {
            *(ptr--) = chars[output & 0xF];
            output >>= 4;
        } while (output && (ptr != buf));
        puts(ptr + 1);
        return *this;
    }
    template <typename T>
    auto operator<<(T x) -> TTY & {
        puts(x);
        return *this;
    }
};
template <>
auto TTY::operator<<<int>(int) -> TTY &;
template <>
auto TTY::operator<<<unsigned int>(unsigned int) -> TTY &;
template <>
auto TTY::operator<<<long long>(long long) -> TTY &;
