#include "../../../hw/raspi2/serial/serial.hpp"
#include "../../../hw/raspi2/vector/vector.hpp"
#include <base.hpp>
#include <config.h>
#include "../../../mmaps/raspi2.mh"
#include "../../../hw/pmm/pmm.hpp"

Serial term;
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
