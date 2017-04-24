#include <tty.hpp>
#include "../../../hw/pc/cgaterm/cgaterm.hpp"
extern "C" void start() {
    CGATerm x = CGATerm();
    x << "Hallo!\n";
}
