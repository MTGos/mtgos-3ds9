#include "../../../hw/3ds11/picafb/picafb.hpp"
#include "../../../hw/3ds11/vectorinit/vectorinit.hpp"
#include <base.hpp>
#include <config.h>
#include "../../../mmaps/3ds11.mh"
#include "../../../hw/pmm/pmm.hpp"

PICAfb term;
PMM_MMAP lpmm;
void main();
extern "C" void start() { main(); }
void drivers_init() {
    pmm=(PMM*)(&lpmm);
    setMainTTY(&term);
    --term;
    initVectors();
    asm volatile("svc #0");
}
