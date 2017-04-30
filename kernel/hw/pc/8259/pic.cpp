#include "pic.hpp"
#include "../io.hpp"
#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI 0x20
#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10

#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_SLAVE 0x04
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM 0x10
namespace PIC {
auto sendEOI(bool slave) -> void {
    if (slave) { out<unsigned char>(PIC2_COMMAND, PIC_EOI); }
    out<unsigned char>(PIC1_COMMAND, PIC_EOI);
}
auto initPIC(int off1, int off2) -> void {
    uint8_t a1 = in<uint8_t>(PIC1_DATA);
    uint8_t a2 = in<uint8_t>(PIC2_DATA);

    out<uint8_t>(PIC1_COMMAND, ICW1_INIT + ICW1_ICW4);
    out<uint8_t>(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);
    out<uint8_t>(PIC1_DATA, off1);
    out<uint8_t>(PIC2_DATA, off2);
    out<uint8_t>(PIC1_DATA, 4); // Slave at 2
    out<uint8_t>(PIC2_DATA, 2); // Self at 2

    out<uint8_t>(PIC1_DATA, ICW4_8086);
    out<uint8_t>(PIC2_DATA, ICW4_8086);

    out(PIC1_DATA, a1);
    out(PIC2_DATA, a2);
}
auto disable() -> void {
    out<uint8_t>(PIC1_DATA, 0xFF);
    out<uint8_t>(PIC2_DATA, 0xFF);
}
auto mask(int no) -> void {
    if (no < 8) {
        out<uint8_t>(PIC1_DATA, in<uint8_t>(PIC1_DATA) | (1 << no));
    } else {
        no -= 8;
        out<uint8_t>(PIC2_DATA, in<uint8_t>(PIC2_DATA) | (1 << no));
    }
}
auto unmask(int no) -> void {
    if (no < 8) {
        out<uint8_t>(PIC1_DATA, in<uint8_t>(PIC1_DATA) & ~(1 << no));
    } else {
        no -= 8;
        out<uint8_t>(PIC2_DATA, in<uint8_t>(PIC2_DATA) & ~(1 << no));
    }
}
auto disableSlave() -> void { mask(2); }
auto enableSlave() -> void { unmask(2); }
auto isSpurious(bool slave) -> bool {
    if (slave) {
        out<uint8_t>(PIC2_COMMAND, 0x0B);
        io_wait();
        if (!(in<uint8_t>(PIC2_DATA) & 0x80)) {
            sendEOI(false);
            return true;
        } else {
            return false;
        }
    } else {
        out<uint8_t>(PIC1_COMMAND, 0x0B);
        io_wait();
        return (in<uint8_t>(PIC1_DATA) & 0x80) ? true : false;
    }
}
}
