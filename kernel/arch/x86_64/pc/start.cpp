#include "../../../hw/pc/cgaterm/cgaterm.hpp"
#include <base.hpp>
CGATerm term;
void main();
extern "C" void start() { main(); }
void drivers_init() {
    setMainTTY(&term);
    --term;
}
