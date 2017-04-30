#pragma once
#include <stdint.h>
/**
 * Namespace contains function to control the Programmable Interrupt Controller
 */
namespace PIC {
auto sendEOI(bool slave) -> void;         ///< Signals the PIC that the interrupt has ended
auto initPIC(int off1, int off2) -> void; ///< Initializes the pic/remaps it
auto disable() -> void;                   ///< disables PIC completely
auto maskIRQ(int no) -> void;             ///< disables a single IRQ
auto unmaskIRQ(int no) -> void;           ///< reenables a single IRQ
auto disableSlave() -> void;              ///< disables IRQ2 and 8-15
auto enableSlave() -> void;               ///< reenables at least IRQ2
auto isSpurious(bool slave) -> bool;      ///< Return if this isn't an actual IRQ.
}
