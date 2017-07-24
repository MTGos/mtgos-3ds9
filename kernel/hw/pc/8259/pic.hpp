#pragma once
#include <stdint.h>
#include <irq.hpp>
struct IRQ_PIC: IRQ {
    IRQ_PIC();
    virtual ~IRQ_PIC();
    virtual void* handleIRQ(void *data);
    virtual void mask(int number);
    virtual void unmask(int number);
};
/**
 * Namespace contains function to control the Programmable Interrupt Controller
 */
namespace PIC {
auto sendEOI(bool slave) -> void;         ///< Signals the PIC that the interrupt has ended
auto initPIC(int off1, int off2) -> void; ///< Initializes the pic/remaps it
auto disable() -> void;                   ///< disables PIC completely
auto mask(int no) -> void;             ///< disables a single IRQ
auto unmask(int no) -> void;           ///< reenables a single IRQ
auto disableSlave() -> void;              ///< disables IRQ2 and 8-15
auto enableSlave() -> void;               ///< reenables at least IRQ2
auto isSpurious(bool slave) -> bool;      ///< Return if this isn't an actual IRQ.
}
