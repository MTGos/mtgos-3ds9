#pragma once
#include "../../../config.h"
constexpr int same_string(char const* lhs, char const* rhs) {
    return !__builtin_strcmp(lhs, rhs);
}
constexpr int get_max_irq() {
    if constexpr(same_string(ARCH, "x86") || same_string(ARCH, "x86_64")) {
        return 32;
    } else if constexpr(same_string(SYSTEM, "3ds9")) {
        return 32;
    } else if constexpr(same_string(SYSTEM, "3ds11")) {
        return 256;
    } else {
        return 32;
    }
}
#define MAX_IRQ get_max_irq()
struct IRQ {
    void*(*handlers[MAX_IRQ])(void*);
    IRQ();
    virtual ~IRQ();
    virtual void* handleIRQ(void *data);
    virtual void mask(int number);
    virtual void unmask(int number);
};
extern IRQ *irqs;
