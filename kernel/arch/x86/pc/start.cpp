#include <base.hpp>
#include "../../../hw/pc/cgaterm/cgaterm.hpp"
CGATerm term;
void main();
extern "C" void start() {
    main();
}
void drivers_init() {
    setMainTTY(&term);
    --term;
}
