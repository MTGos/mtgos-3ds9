#include "../../../hw/3ds9/picafb/picafb.hpp"
#include "../../../hw/3ds9/vectorinit/vectorinit.hpp"
#include <base.hpp>
#include <config.h>
#include "../../../mmaps/3ds9.mh"
#include "../../../hw/pmm/pmm.hpp"

PICAfb term;
PMM_MMAP lpmm;
void main();
extern "C" void enable_irqs();
extern "C" void start() { main();
    for(;;);
}
void drivers_init() {
    pmm=(PMM*)(&lpmm);
    setMainTTY(&term);
    --term;
    //Init 1000Hz timer
    enable_irqs();
    *((volatile uint16_t*)0x10003002)=0;
    *((volatile uint16_t*)0x10003000)=65;
    *((volatile uint16_t*)0x10003002)=0b11000000;
    *((volatile uint32_t*)0x10001000)|=1<<8;
}
