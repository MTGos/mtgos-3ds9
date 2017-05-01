#include "../../../hw/3ds9/picafb/picafb.hpp"
#include "../../../hw/3ds9/vectorinit/vectorinit.hpp"
#include <base.hpp>
#include <config.h>

PICAfb term;
void main();
extern "C" void start() { main(); }
void drivers_init() {
    term << "initing main tty\n";
    setMainTTY(&term);
    --term;
    term << "Initing vectors\n";
    initVectors();
    term << "trying svc\n";
    asm volatile("svc #0");
}
