#include "../../../hw/raspi2/serial/serial.hpp"
#include "../../../hw/raspi2/vector/vector.hpp"
#include <base.hpp>
#include <config.h>

Serial term;
void main();
extern "C" void start() { main(); }
void drivers_init() {
    setMainTTY(&term);
    --term;
    initVectors();
    asm volatile("svc #0");
}
