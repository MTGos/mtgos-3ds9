#include "../../../hw/3ds9/picafb/picafb.hpp"
#include "../../../hw/3ds9/vectorinit/vectorinit.hpp"
#include <base.hpp>
#include <config.h>
#include "../../../mmaps/3ds9.mh"

PICAfb term;
void main();
extern "C" void start() { main();
    for(;;);
}
void drivers_init() {
    setMainTTY(&term);
    --term;
    initVectors();
    asm volatile("svc #0");
}
