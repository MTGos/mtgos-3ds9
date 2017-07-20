#include "../../../hw/3ds11/picafb/picafb.hpp"
#include "../../../hw/3ds11/vectorinit/vectorinit.hpp"
#include <base.hpp>
#include <config.h>
#include "../../../mmaps/3ds11.mh"

PICAfb term;
void main();
extern "C" void start() { main(); }
void drivers_init() {
    setMainTTY(&term);
    --term;
    initVectors();
    asm volatile("svc #0");
}
