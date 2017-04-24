#include <base.hpp>
void drivers_init();
extern "C" void(*start_ctors)();
extern "C" void(*end_ctors)();
extern "C" void(*start_dtors)();
extern "C" void(*end_dtors)();
void main() {
    for(auto ctor=&start_ctors;ctor<&end_ctors;ctor++)
        (**ctor)();
    drivers_init();
    *out << "Hallo!\n";
    for(auto dtor=&start_dtors;dtor!=&end_dtors;dtor++)
        (**dtor)();
}
