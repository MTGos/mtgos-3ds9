#pragma once
#include <kobject.hpp>
/**
 * The colors that are supported on TTYs that don't understand RGB colors.
 */
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
/**
 * TTY class. It is used for outputting text on some sort of screen. It supports unicode and at least 16 colors.
 */
class TTY : public Kobject {
    protected:
    int x;                                              ///< current X position on the screen
    int y;                                              ///< current Y on the screen
    int width;                                          ///< width of the screen
    int height;                                         ///< height of the screen
    Color curColor;                                     ///< one of the 16 colors
    unsigned int rgbColor;                              ///< RGB888 color
    bool useRGB;                                        ///< true if the rgbColor is used instead of the curColor.
    virtual auto plotChar(int x, int y, int c) -> void; ///< plots a single character on the screen.

    public:
    TTY(int width, int height);
    virtual ~TTY();
    virtual auto rgbSupport()
        -> bool; ///< returns true if RGB colors can be used. Note that some colors might be same on some TTYs.
    virtual auto setColor(Color c) -> void;        ///< sets the color to one of the 16 required
    virtual auto setColor(unsigned int c) -> void; ///< sets the color to a RGB888 color.
    virtual auto putChar(int c) -> void;           ///< prints a unicode codepoint on the TTY
    virtual auto puts(const char *s) -> void;      ///< prints a UTF-8 string
    /**
     * Outputs an integer of base16 on the screen. Works with any type that you can shift and dereference arrays with.
     */
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
    /**
     * Outputs a arbitrary type, as long as it can be casted to const char* or has a template overload.
     */
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
