#include "../../../hw/3ds11/picafb/picafb.hpp"
#include <base.hpp>
#include <config.h>

PICAfb term;
void main();
extern "C" void start() { main(); }
void drivers_init() {
    setMainTTY(&term);
    --term;
}
