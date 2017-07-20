#pragma once
#include <stdint.h>
enum class UART_MEM: uint32_t {
    GPPUD =     0x94,
    GPPUDCLK0 = 0x98,
    DR =        0x00,
    RSRECR =    0x04,
    FR =        0x18,
    ILPR =      0x20,
    IBRD =      0x24,
    FBRD =      0x28,
    LCRH =      0x2C,
    CR   =      0x30,
    IFLS =      0x34,
    IMSC =      0x38,
    RIS  =      0x3C,
    MIS  =      0x40,
    ICR  =      0x44,
    DMACR =     0x48,
    ITCR =      0x80,
    ITIP =      0x84,
    ITOP =      0x88,
    TDR  =      0x8C
};
class UART {
    public:
        static UART &getInstance();
        uint32_t &operator[](uint32_t off); ///< Returns a reference to the corresponding MMIO register
        uint32_t &operator[](UART_MEM off); ///< @see UART::operator[](uint32_t off);
        UART(UART const&) = delete;
        UART &operator=(UART const&) = delete;
    private:
        UART();
};
