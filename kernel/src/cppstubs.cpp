#include <stdint.h>
#include <stddef.h>
extern "C" void __cxa_pure_virtual() {
    //panic("Pure virtual function called.");
}
void * operator new(size_t s) {
    return (void*)1;
}
void * operator new[](size_t s) {
    return (void*)1;
}
void operator delete(void* p) {}
void operator delete[](void* p) {}
void operator delete(void* p, size_t s) {}
void operator delete[](void* p, size_t s) {}
void * operator new(size_t s, void* p) {return p;}
void * operator new[](size_t s, void* p) {return p;}
void operator delete(void *, void *p) {}
void operator delete[](void *, void *p) {}

