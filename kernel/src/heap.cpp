#include <base.hpp>
#include <stddef.h>
//Shitty heap which wastes a ton of bytes and page-aligns everything
void *operator new(size_t s) {
    return (void*)(*pmm, (s+4095)/4096);
}
void *operator new[](size_t s) {
    return (void*)(*pmm, (s+4095)/4096);
}
void *operator delete(void *p) {
    (*pmm)((phys_t)p,1);
}
void *operator delete[](void *p) {
    (*pmm)((phys_t)p,1);
}
void *operator delete(void *p, size_t s) {
    (*pmm)((phys_t)p,(s+4095)/4096);
}
void *operator delete[](void *p, size_t s) {
    (*pmm)((phys_t)p,(s+4095)/4096);
}
