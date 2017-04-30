#include "../../../hw/3ds9/picafb/picafb.hpp"
#include "../../../hw/3ds9/vectorinit/vectorinit.hpp"
#include <base.hpp>
#include <config.h>

PICAfb term;
void main();
extern "C" void start() { main(); }
void drivers_init() {
    setMainTTY(&term);
    --term;
}
