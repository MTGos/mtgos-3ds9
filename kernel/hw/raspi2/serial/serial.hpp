#pragma once
#include "../uart/uart.hpp"
#include <base.hpp>
class Serial: public TTY {
    private:
        UART &uart;
        auto serial_putc(int c) -> void;
        auto serial_putc(char c) -> void;
        auto serial_puti(int i) -> void;
    protected:
        virtual auto plotChar(int x, int y, int c) -> void;
    public:
        Serial();
};
